const request = require('supertest');
const express = require('express');
const cors = require('cors');
const initSqlJs = require('sql.js');
const bcrypt = require('bcryptjs');

process.env.JWT_SECRET = 'test_secret_key';
process.env.JWT_EXPIRES_IN = '2h';

describe('Goods API', () => {
  let app;
  let testDb;
  let userToken;

  async function setupTestDb() {
    const SQL = await initSqlJs();
    const db = new SQL.Database();

    db.run(`CREATE TABLE IF NOT EXISTS users (
      id INTEGER PRIMARY KEY AUTOINCREMENT,
      username TEXT UNIQUE NOT NULL,
      password TEXT NOT NULL,
      role INTEGER DEFAULT 0,
      create_time DATETIME DEFAULT CURRENT_TIMESTAMP
    )`);

    db.run(`CREATE TABLE IF NOT EXISTS goods (
      id INTEGER PRIMARY KEY AUTOINCREMENT,
      seller_id INTEGER NOT NULL,
      title TEXT NOT NULL,
      description TEXT,
      price REAL NOT NULL,
      category TEXT,
      status INTEGER DEFAULT 0,
      create_time DATETIME DEFAULT CURRENT_TIMESTAMP
    )`);

    db.run(`CREATE TABLE IF NOT EXISTS interactions (
      id INTEGER PRIMARY KEY AUTOINCREMENT,
      user_id INTEGER NOT NULL,
      goods_id INTEGER NOT NULL,
      content TEXT,
      type INTEGER NOT NULL,
      create_time DATETIME DEFAULT CURRENT_TIMESTAMP
    )`);

    return db;
  }

  beforeEach(async () => {
    jest.resetModules();

    testDb = await setupTestDb();

    const dbModule = require('../utils/db');
    await dbModule.initDatabase(testDb);

    const authRoutes = require('../routes/auth');
    const goodsRoutes = require('../routes/goods');

    app = express();
    app.use(cors());
    app.use(express.json());
    app.use('/api/auth', authRoutes);
    app.use('/api/goods', goodsRoutes);

    const userResponse = await request(app)
      .post('/api/auth/register')
      .send({ username: 'goodstest', password: 'goods123' });
    userToken = userResponse.body.token;
  });

  afterEach(() => {
    if (testDb) {
      testDb.close();
    }
  });

  describe('GET /api/goods', () => {
    it('should get empty goods list', async () => {
      const response = await request(app).get('/api/goods');
      expect(response.status).toBe(200);
      expect(response.body).toEqual([]);
    });

    it('should get goods list with items', async () => {
      await request(app)
        .post('/api/goods')
        .set('Authorization', `Bearer ${userToken}`)
        .send({
          title: 'Test Item',
          description: 'Test Description',
          price: 100.00,
          category: '电子设备'
        });

      const response = await request(app).get('/api/goods');
      expect(response.status).toBe(200);
      expect(response.body.length).toBe(1);
      expect(response.body[0]).toHaveProperty('title', 'Test Item');
    });
  });

  describe('POST /api/goods', () => {
    it('should create goods successfully', async () => {
      const response = await request(app)
        .post('/api/goods')
        .set('Authorization', `Bearer ${userToken}`)
        .send({
          title: 'New Item',
          description: 'Brand new',
          price: 150.50,
          category: '运动器材'
        });

      expect(response.status).toBe(201);
      expect(response.body).toHaveProperty('message', '商品发布成功');
      expect(response.body).toHaveProperty('id');
    });

    it('should return error without token', async () => {
      const response = await request(app)
        .post('/api/goods')
        .send({ title: 'New Item', price: 100 });

      expect(response.status).toBe(401);
      expect(response.body).toHaveProperty('error', '未提供认证令牌');
    });

    it('should return error when title is missing', async () => {
      const response = await request(app)
        .post('/api/goods')
        .set('Authorization', `Bearer ${userToken}`)
        .send({ price: 100 });

      expect(response.status).toBe(400);
      expect(response.body).toHaveProperty('error', '商品标题和价格不能为空');
    });
  });

  describe('PUT /api/goods/:id', () => {
    let goodsId;

    beforeEach(async () => {
      const createResponse = await request(app)
        .post('/api/goods')
        .set('Authorization', `Bearer ${userToken}`)
        .send({
          title: 'Old Title',
          price: 100,
          category: '其他'
        });
      goodsId = createResponse.body.id;
    });

    it('should update goods successfully', async () => {
      const response = await request(app)
        .put(`/api/goods/${goodsId}`)
        .set('Authorization', `Bearer ${userToken}`)
        .send({
          title: 'Updated Title',
          price: 150
        });

      expect(response.status).toBe(200);
      expect(response.body).toHaveProperty('message', '商品更新成功');
    });
  });

  describe('DELETE /api/goods/:id', () => {
    let goodsId;

    beforeEach(async () => {
      const createResponse = await request(app)
        .post('/api/goods')
        .set('Authorization', `Bearer ${userToken}`)
        .send({
          title: 'To Be Deleted',
          price: 50,
          category: '其他'
        });
      goodsId = createResponse.body.id;
    });

    it('should delete goods successfully', async () => {
      const response = await request(app)
        .delete(`/api/goods/${goodsId}`)
        .set('Authorization', `Bearer ${userToken}`);

      expect(response.status).toBe(200);
      expect(response.body).toHaveProperty('message', '商品删除成功');
    });
  });
});