const initSqlJs = require('sql.js');
const fs = require('fs');
const path = require('path');

const dbPath = path.join(__dirname, '../db/campus.db');

let db = null;
let initialized = false;

async function initDatabase() {
  const SQL = await initSqlJs();
  
  if (fs.existsSync(dbPath)) {
    const data = fs.readFileSync(dbPath);
    db = new SQL.Database(data);
  } else {
    db = new SQL.Database();
  }

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

  const countResult = db.exec('SELECT COUNT(*) as count FROM users WHERE username = "admin"');
  const count = countResult.length > 0 ? countResult[0].values[0][0] : 0;

  if (count === 0) {
    const bcrypt = require('bcryptjs');
    const hashedPassword = bcrypt.hashSync('admin123', 10);
    db.run('INSERT INTO users (username, password, role) VALUES ("' + 'admin' + '", "' + hashedPassword + '", 1)');
    console.log('初始管理员账号已创建: admin/admin123');
  }

  saveDatabase();
  initialized = true;
  console.log('成功连接到SQLite数据库');
}

function saveDatabase() {
  if (db) {
    const data = db.export();
    fs.writeFileSync(dbPath, Buffer.from(data));
  }
}

function queryOne(sql, params = []) {
  let paramSql = sql;
  params.forEach((param, idx) => {
    const escaped = typeof param === 'string' ? '"' + param.replace(/"/g, '""') + '"' : param;
    paramSql = paramSql.replace('?', escaped);
  });
  
  const result = db.exec(paramSql);
  
  if (result.length === 0 || result[0].values.length === 0) {
    return null;
  }
  
  const columns = result[0].columns;
  const row = result[0].values[0];
  const obj = {};
  columns.forEach((col, idx) => {
    obj[col.toLowerCase()] = row[idx];
  });
  return obj;
}

function queryAll(sql, params = []) {
  let paramSql = sql;
  params.forEach((param, idx) => {
    const escaped = typeof param === 'string' ? '"' + param.replace(/"/g, '""') + '"' : param;
    paramSql = paramSql.replace('?', escaped);
  });
  
  const result = db.exec(paramSql);
  if (result.length === 0) return [];
  
  const columns = result[0].columns;
  const rows = result[0].values;
  
  return rows.map(row => {
    const obj = {};
    columns.forEach((col, idx) => {
      obj[col.toLowerCase()] = row[idx];
    });
    return obj;
  });
}

function execute(sql, params = []) {
  let paramSql = sql;
  params.forEach((param, idx) => {
    const escaped = typeof param === 'string' ? '"' + param.replace(/"/g, '""') + '"' : param;
    paramSql = paramSql.replace('?', escaped);
  });
  
  db.run(paramSql);
  saveDatabase();
  
  const result = db.exec('SELECT last_insert_rowid() as id, changes() as changes');
  const values = result[0].values[0];
  return { id: values[0], changes: values[1] };
}

initDatabase();

module.exports = {
  get db() { return db; },
  get initialized() { return initialized; },
  saveDatabase,
  queryOne,
  queryAll,
  execute,
  initDatabase
};
