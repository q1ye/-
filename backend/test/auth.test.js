const request = require('supertest');
const express = require('express');
const cors = require('cors');
const initSqlJs = require('sql.js');
const bcrypt = require('bcryptjs');

describe('Authentication API', () => {
  let app;
  let testDb;

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

    const hashedPassword = bcrypt.hashSync('admin123', 10);
    db.run('INSERT INTO users (username, password, role) VALUES (?, ?, ?)', ['admin', hashedPassword, 1]);

    return db;
  }

  beforeEach(async () => {
    jest.resetModules();

    process.env.JWT_SECRET = 'test_secret_key';
    process.env.JWT_EXPIRES_IN = '2h';

    testDb = await setupTestDb();

    const dbModule = require('../utils/db');
    await dbModule.initDatabase(testDb);

    app = express();
    app.use(cors());
    app.use(express.json());

    const authRoutes = require('../routes/auth');
    app.use('/api/auth', authRoutes);
  });

  afterEach(() => {
    if (testDb) {
      testDb.close();
    }
  });

  describe('POST /api/auth/register', () => {
    it('should register a new user successfully', async () => {
      const response = await request(app)
        .post('/api/auth/register')
        .send({ username: 'testuser', password: 'test123456' });

      expect(response.status).toBe(201);
      expect(response.body).toHaveProperty('message', '注册成功');
      expect(response.body).toHaveProperty('token');
      expect(response.body.user).toHaveProperty('username', 'testuser');
      expect(response.body.user).toHaveProperty('role', 0);
    });

    it('should return error when username already exists', async () => {
      await request(app)
        .post('/api/auth/register')
        .send({ username: 'existinguser', password: 'password123' });

      const response = await request(app)
        .post('/api/auth/register')
        .send({ username: 'existinguser', password: 'password456' });

      expect(response.status).toBe(400);
      expect(response.body).toHaveProperty('error', '用户名已存在');
    });

    it('should return error when username is missing', async () => {
      const response = await request(app)
        .post('/api/auth/register')
        .send({ password: 'password123' });

      expect(response.status).toBe(400);
      expect(response.body).toHaveProperty('error', '用户名和密码不能为空');
    });

    it('should return error when password is missing', async () => {
      const response = await request(app)
        .post('/api/auth/register')
        .send({ username: 'testuser' });

      expect(response.status).toBe(400);
      expect(response.body).toHaveProperty('error', '用户名和密码不能为空');
    });
  });

  describe('POST /api/auth/login', () => {
    beforeEach(async () => {
      await request(app)
        .post('/api/auth/register')
        .send({ username: 'loginuser', password: 'login123' });
    });

    it('should login successfully with correct credentials', async () => {
      const response = await request(app)
        .post('/api/auth/login')
        .send({ username: 'loginuser', password: 'login123' });

      expect(response.status).toBe(200);
      expect(response.body).toHaveProperty('message', '登录成功');
      expect(response.body).toHaveProperty('token');
      expect(response.body.user).toHaveProperty('username', 'loginuser');
    });

    it('should return error with wrong password', async () => {
      const response = await request(app)
        .post('/api/auth/login')
        .send({ username: 'loginuser', password: 'wrongpassword' });

      expect(response.status).toBe(401);
      expect(response.body).toHaveProperty('error', '用户名或密码错误');
    });

    it('should return error for non-existent user', async () => {
      const response = await request(app)
        .post('/api/auth/login')
        .send({ username: 'nonexistent', password: 'password123' });

      expect(response.status).toBe(401);
      expect(response.body).toHaveProperty('error', '用户名或密码错误');
    });

    it('should return error when username is missing', async () => {
      const response = await request(app)
        .post('/api/auth/login')
        .send({ password: 'password123' });

      expect(response.status).toBe(400);
      expect(response.body).toHaveProperty('error', '用户名和密码不能为空');
    });

    it('should return error when password is missing', async () => {
      const response = await request(app)
        .post('/api/auth/login')
        .send({ username: 'loginuser' });

      expect(response.status).toBe(400);
      expect(response.body).toHaveProperty('error', '用户名和密码不能为空');
    });

    it('should login successfully with admin credentials', async () => {
      const response = await request(app)
        .post('/api/auth/login')
        .send({ username: 'admin', password: 'admin123' });

      expect(response.status).toBe(200);
      expect(response.body).toHaveProperty('message', '登录成功');
      expect(response.body.user).toHaveProperty('role', 1);
    });
  });
});