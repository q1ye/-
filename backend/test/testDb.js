const initSqlJs = require('sql.js');
const bcrypt = require('bcryptjs');

let testDbInstance = null;

async function createTestDb() {
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

async function getTestDb() {
  if (!testDbInstance) {
    testDbInstance = await createTestDb();
  }
  return testDbInstance;
}

function setTestDb(db) {
  testDbInstance = db;
}

function resetTestDb() {
  if (testDbInstance) {
    testDbInstance.close();
    testDbInstance = null;
  }
}

module.exports = {
  getTestDb,
  setTestDb,
  resetTestDb,
  createTestDb
};