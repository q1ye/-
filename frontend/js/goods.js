import { getGoods, createGoods, deleteGoods } from './api.js';

let currentCategory = '';
let currentSearch = '';

function checkAuth() {
  const token = localStorage.getItem('token');
  if (!token) {
    window.location.href = 'index.html';
    return false;
  }
  return true;
}

function getUser() {
  const userStr = localStorage.getItem('user');
  return userStr ? JSON.parse(userStr) : null;
}

function isAdmin() {
  const user = getUser();
  return user && user.role === 1;
}

function logout() {
  localStorage.removeItem('token');
  localStorage.removeItem('user');
  window.location.href = 'index.html';
}

function searchGoods() {
  currentSearch = document.getElementById('search-input').value.trim();
  loadGoods();
}

function filterByCategory(category) {
  currentCategory = category;
  document.querySelectorAll('.category-btn').forEach(btn => {
    btn.classList.remove('active');
  });
  event.target.classList.add('active');
  loadGoods();
}

async function deleteGoodsItem(id) {
  if (!confirm('确定要删除这个商品吗？')) return;

  try {
    await deleteGoods(id);
    loadGoods();
  } catch (error) {
    alert('删除失败: ' + error.message);
  }
}

async function loadGoods() {
  if (!checkAuth()) return;

  try {
    const query = {};
    if (currentSearch) query.search = currentSearch;
    if (currentCategory) query.category = currentCategory;

    const goods = await getGoods(query);
    const container = document.getElementById('goods-container');

    if (goods.length === 0) {
      container.innerHTML = '<div style="text-align: center; color: white; padding: 40px;">暂无商品</div>';
      return;
    }

    container.innerHTML = goods.map(g => `
      <div class="goods-card" data-id="${g.id}">
        <h3>${g.title}</h3>
        <p class="price">¥${parseFloat(g.price).toFixed(2)}</p>
        <p class="seller">卖家: ${g.seller_name}</p>
        <p>${g.description || '暂无描述'}</p>
        <div class="card-actions">
          <button class="buy-btn">立即购买</button>
          ${g.isOwner || isAdmin() ? `
            <button class="delete-btn" data-delete-id="${g.id}">删除</button>
          ` : ''}
        </div>
      </div>
    `).join('');

    container.querySelectorAll('.delete-btn').forEach(btn => {
      btn.addEventListener('click', (e) => {
        const id = parseInt(e.target.dataset.deleteId);
        deleteGoodsItem(id);
      });
    });

    renderAdminFeatures();
  } catch (error) {
    alert('加载商品失败: ' + error.message);
  }
}

function renderAdminFeatures() {
  const adminPanel = document.getElementById('admin-panel');
  if (adminPanel) {
    adminPanel.style.display = isAdmin() ? 'block' : 'none';
  }
}

function initDashboard() {
  if (!checkAuth()) return;

  const user = getUser();
  const usernameDisplay = document.getElementById('username-display');
  if (usernameDisplay) {
    usernameDisplay.textContent = user.username + (user.role === 1 ? ' (管理员)' : '');
  }

  document.getElementById('logout-btn').addEventListener('click', logout);
  document.getElementById('search-btn').addEventListener('click', searchGoods);
  
  document.getElementById('search-input').addEventListener('keypress', (e) => {
    if (e.key === 'Enter') searchGoods();
  });

  document.querySelectorAll('.category-btn').forEach(btn => {
    btn.addEventListener('click', (e) => {
      filterByCategory(e.target.dataset.category);
    });
  });

  renderAdminFeatures();
  loadGoods();
}

function initPublish() {
  if (!checkAuth()) return;

  document.getElementById('publish-form').addEventListener('submit', async (e) => {
    e.preventDefault();

    const title = document.getElementById('title').value.trim();
    const description = document.getElementById('description').value.trim();
    const price = parseFloat(document.getElementById('price').value);
    const category = document.getElementById('category').value;

    if (!title) {
      showError('请输入商品标题');
      return;
    }

    if (!price || price <= 0) {
      showError('请输入有效的价格');
      return;
    }

    try {
      await createGoods({ title, description, price, category });
      alert('商品发布成功！');
      window.location.href = 'dashboard.html';
    } catch (error) {
      showError(error.message);
    }
  });
}

function showError(message) {
  const errorElement = document.getElementById('error-message');
  if (errorElement) {
    errorElement.textContent = message;
    errorElement.style.display = 'block';
  }
}

document.addEventListener('DOMContentLoaded', () => {
  if (window.location.pathname.includes('dashboard')) {
    initDashboard();
  } else if (window.location.pathname.includes('publish')) {
    initPublish();
  }
});
