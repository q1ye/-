const API_BASE = 'http://localhost:3000/api';

export const request = async (endpoint, method = 'GET', data = null) => {
  const options = {
    method,
    headers: {
      'Content-Type': 'application/json',
      'Authorization': `Bearer ${localStorage.getItem('token') || ''}`
    }
  };

  if (data) options.body = JSON.stringify(data);

  const response = await fetch(`${API_BASE}${endpoint}`, options);
  const result = await response.json();

  if (!response.ok) {
    throw new Error(result.error || 'API请求失败');
  }

  return result;
};

export const login = (credentials) =>
  request('/auth/login', 'POST', credentials);

export const register = (userData) =>
  request('/auth/register', 'POST', userData);

export const getGoods = (query = {}) => {
  const params = new URLSearchParams(query);
  return request(`/goods?${params.toString()}`, 'GET');
};

export const getGoodsById = (id) =>
  request(`/goods/${id}`, 'GET');

export const createGoods = (goodsData) =>
  request('/goods', 'POST', goodsData);

export const updateGoods = (id, goodsData) =>
  request(`/goods/${id}`, 'PUT', goodsData);

export const deleteGoods = (id) =>
  request(`/goods/${id}`, 'DELETE');

export const adminDeleteGoods = (id) =>
  request(`/goods/admin/${id}`, 'DELETE');
