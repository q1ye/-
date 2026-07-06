const express = require('express');
const router = express.Router();
const goodsController = require('../controllers/goodsController');
const { verifyToken, isAdmin } = require('../controllers/authController');

router.get('/', goodsController.getAllGoods);
router.get('/:id', goodsController.getGoodsById);
router.post('/', verifyToken, goodsController.createGoods);
router.put('/:id', verifyToken, goodsController.updateGoods);
router.delete('/:id', verifyToken, goodsController.deleteGoods);
router.delete('/admin/:id', verifyToken, isAdmin, goodsController.adminDeleteGoods);

module.exports = router;
