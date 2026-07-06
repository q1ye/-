import { login, register } from './api.js';

window.switchTab = (tab) => {
  const loginForm = document.getElementById('login-form');
  const registerForm = document.getElementById('register-form');
  const loginBtn = document.querySelectorAll('.tab-btn')[0];
  const registerBtn = document.querySelectorAll('.tab-btn')[1];

  if (tab === 'login') {
    loginForm.classList.remove('hidden');
    registerForm.classList.add('hidden');
    loginBtn.classList.add('active');
    registerBtn.classList.remove('active');
  } else {
    loginForm.classList.add('hidden');
    registerForm.classList.remove('hidden');
    loginBtn.classList.remove('active');
    registerBtn.classList.add('active');
  }
  hideError();
};

function showError(message) {
  const errorElement = document.getElementById('error-message');
  errorElement.textContent = message;
  errorElement.style.display = 'block';
}

function hideError() {
  const errorElement = document.getElementById('error-message');
  errorElement.style.display = 'none';
}

document.getElementById('login-form').addEventListener('submit', async (e) => {
  e.preventDefault();
  hideError();

  const username = document.getElementById('login-username').value.trim();
  const password = document.getElementById('login-password').value;

  if (!username || !password) {
    showError('请输入用户名和密码');
    return;
  }

  try {
    const result = await login({ username, password });
    localStorage.setItem('token', result.token);
    localStorage.setItem('user', JSON.stringify(result.user));
    window.location.href = 'dashboard.html';
  } catch (error) {
    showError(error.message);
  }
});

document.getElementById('register-form').addEventListener('submit', async (e) => {
  e.preventDefault();
  hideError();

  const username = document.getElementById('register-username').value.trim();
  const password = document.getElementById('register-password').value;

  if (!username || !password) {
    showError('请输入用户名和密码');
    return;
  }

  if (password.length < 6) {
    showError('密码长度至少为6位');
    return;
  }

  try {
    const result = await register({ username, password });
    localStorage.setItem('token', result.token);
    localStorage.setItem('user', JSON.stringify(result.user));
    window.location.href = 'dashboard.html';
  } catch (error) {
    showError(error.message);
  }
});
