const { queryOne, queryAll, execute } = require('../utils/db');

class Goods {
  static create(sellerId, title, description, price, category) {
    const result = execute('INSERT INTO goods (seller_id, title, description, price, category) VALUES (?, ?, ?, ?, ?)', 
      [sellerId, title, description, price, category]);
    return { id: result.id };
  }

  static getAll(query = {}) {
    let sql = 'SELECT g.*, u.username as seller_name FROM goods g JOIN users u ON g.seller_id = u.id WHERE g.status = 0';
    const params = [];

    if (query.search) {
      sql += ' AND (g.title LIKE ? OR g.description LIKE ?)';
      params.push(`%${query.search}%`, `%${query.search}%`);
    }

    if (query.category) {
      sql += ' AND g.category = ?';
      params.push(query.category);
    }

    sql += ' ORDER BY g.create_time DESC';

    return queryAll(sql, params);
  }

  static getById(id) {
    return queryOne('SELECT g.*, u.username as seller_name FROM goods g JOIN users u ON g.seller_id = u.id WHERE g.id = ?', [id]);
  }

  static update(id, data) {
    const { title, description, price, category, status } = data;
    let sql = 'UPDATE goods SET';
    const params = [];
    const updates = [];

    if (title) { updates.push('title = ?'); params.push(title); }
    if (description) { updates.push('description = ?'); params.push(description); }
    if (price) { updates.push('price = ?'); params.push(price); }
    if (category) { updates.push('category = ?'); params.push(category); }
    if (status !== undefined) { updates.push('status = ?'); params.push(status); }

    sql += updates.join(', ') + ' WHERE id = ?';
    params.push(id);

    const result = execute(sql, params);
    return { affectedRows: result.changes };
  }

  static delete(id) {
    const result = execute('DELETE FROM goods WHERE id = ?', [id]);
    return { affectedRows: result.changes };
  }

  static getBySellerId(sellerId) {
    return queryAll('SELECT * FROM goods WHERE seller_id = ? ORDER BY create_time DESC', [sellerId]);
  }
}

module.exports = Goods;
