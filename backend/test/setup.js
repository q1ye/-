const initSqlJs = require('sql.js');
const bcrypt = require('bcryptjs');

global.testDb = null;

async function createTestDb() {
  const SQL = await initSqlJs();
  const testDb = new SQL.Database();

  testDb.run(`CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password TEXT NOT NULL,
    role INTEGER DEFAULT 0,
    create_time DATETIME DEFAULT CURRENT_TIMESTAMP
  )`);

  testDb.run(`CREATE TABLE IF NOT EXISTS goods (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    seller_id INTEGER NOT NULL,
    title TEXT NOT NULL,
    description TEXT,
    price REAL NOT NULL,
    category TEXT,
    status INTEGER DEFAULT 0,
    create_time DATETIME DEFAULT CURRENT_TIMESTAMP
  )`);

  testDb.run(`CREATE TABLE IF NOT EXISTS interactions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER NOT NULL,
    goods_id INTEGER NOT NULL,
    content TEXT,
    type INTEGER NOT NULL,
    create_time DATETIME DEFAULT CURRENT_TIMESTAMP
  )`);

  const hashedPassword = bcrypt.hashSync('admin123', 10);
  testDb.run('INSERT INTO users (username, password, role) VALUES (?, ?, ?)', ['admin', hashedPassword, 1]);

  return testDb;
}

function resetTestDb(testDb) {
  testDb.run('DELETE FROM interactions');
  testDb.run('DELETE FROM goods');
  testDb.run('DELETE FROM users');
  testDb.run('INSERT INTO users (username, password, role) VALUES (?, ?, ?)', [
    'admin',
    bcrypt.hashSync('admin123', 10),
    1
  ]);
}

beforeAll(async () => {
  global.testDb = await createTestDb();
});

afterEach(() => {
  resetTestDb(global.testDb);
});

afterAll(() => {
  if (global.testDb) {
    global.testDb.close();
  }
});

module.exports = { createTestDb, resetTestDb };