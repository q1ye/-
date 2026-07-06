const { queryOne, execute } = require('../utils/db');
const bcrypt = require('bcryptjs');

class User {
  static create(username, password, role = 0) {
    const hashedPassword = bcrypt.hashSync(password, 10);
    const result = execute('INSERT INTO users (username, password, role) VALUES (?, ?, ?)', [username, hashedPassword, role]);
    return { id: result.id, username, role };
  }

  static findByUsername(username) {
    return queryOne('SELECT * FROM users WHERE username = ?', [username]);
  }

  static findById(id) {
    return queryOne('SELECT id, username, role, create_time FROM users WHERE id = ?', [id]);
  }

  static validatePassword(password, hashedPassword) {
    return bcrypt.compareSync(password, hashedPassword);
  }
}

module.exports = User;
