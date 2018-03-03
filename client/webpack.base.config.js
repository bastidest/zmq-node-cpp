var path = require('path');

module.exports = {
  module: {
    rules: [
      {
        test: /\.js$/,
        exclude: /node_modules/,
        loader: 'babel-loader'
      }, {
        test: /\.vue$/,
        loader: 'vue-loader'
      }
    ],
  },
  resolve: {
    modules: [
      'node_modules',
      'vue'
    ]
  },
  devtool: 'source-map',
  target: 'web',
  entry: './src/frontend/index.js',
  output: {
    path: path.resolve('dist') + '/',
    publicPath: 'dist',
    filename: 'bundle.js'
  }
};