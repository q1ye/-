const Goods = require('../models/Goods');

exports.getAllGoods = async (req, res) => {
  try {
    const { search, category } = req.query;
    const goods = await Goods.getAll({ search, category });

    const currentUserId = req.user ? req.user.id : null;
    const goodsWithOwnerInfo = goods.map(g => ({
      ...g,
      isOwner: currentUserId === g.seller_id
    }));

    res.json(goodsWithOwnerInfo);
  } catch (error) {
    res.status(500).json({ error: '获取商品列表失败' });
  }
};

exports.getGoodsById = async (req, res) => {
  try {
    const { id } = req.params;
    const goods = await Goods.getById(id);

    if (!goods) {
      return res.status(404).json({ error: '商品不存在' });
    }

    const currentUserId = req.user ? req.user.id : null;
    goods.isOwner = currentUserId === goods.seller_id;

    res.json(goods);
  } catch (error) {
    res.status(500).json({ error: '获取商品详情失败' });
  }
};

exports.createGoods = async (req, res) => {
  try {
    const { title, description, price, category } = req.body;

    if (!title || !price) {
      return res.status(400).json({ error: '商品标题和价格不能为空' });
    }

    const result = await Goods.create(req.user.id, title, description, price, category);
    res.status(201).json({ message: '商品发布成功', id: result.id });
  } catch (error) {
    res.status(500).json({ error: '发布商品失败' });
  }
};

exports.updateGoods = async (req, res) => {
  try {
    const { id } = req.params;
    const goods = await Goods.getById(id);

    if (!goods) {
      return res.status(404).json({ error: '商品不存在' });
    }

    if (goods.seller_id !== req.user.id && req.user.role !== 1) {
      return res.status(403).json({ error: '无权限修改此商品' });
    }

    const result = await Goods.update(id, req.body);
    if (result.affectedRows === 0) {
      return res.status(404).json({ error: '商品不存在' });
    }

    res.json({ message: '商品更新成功' });
  } catch (error) {
    res.status(500).json({ error: '更新商品失败' });
  }
};

exports.deleteGoods = async (req, res) => {
  try {
    const { id } = req.params;
    const goods = await Goods.getById(id);

    if (!goods) {
      return res.status(404).json({ error: '商品不存在' });
    }

    if (goods.seller_id !== req.user.id && req.user.role !== 1) {
      return res.status(403).json({ error: '无权限删除此商品' });
    }

    const result = await Goods.delete(id);
    if (result.affectedRows === 0) {
      return res.status(404).json({ error: '商品不存在' });
    }

    res.json({ message: '商品删除成功' });
  } catch (error) {
    res.status(500).json({ error: '删除商品失败' });
  }
};

exports.adminDeleteGoods = async (req, res) => {
  try {
    const { id } = req.params;
    const result = await Goods.update(id, { status: 2 });

    if (result.affectedRows === 0) {
      return res.status(404).json({ error: '商品不存在' });
    }

    res.json({ message: '商品已强制下架' });
  } catch (error) {
    res.status(500).json({ error: '下架商品失败' });
  }
};
