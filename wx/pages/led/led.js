// pages/stock/stock.js
//加载插件

Page({

  data: {
    ss: "1",
    zt: 'red',
    ms: 'wx@ssdk',
    led:'0'
  },
  onLoad: function(options) {
    this.data.ss
    var ssdk = "sssdsdk"
    //建立连接
    wx.onSocketOpen(function () {
      wx.sendSocketMessage({
        data: 'wx@ssdk',
      })
    }),
    //连接成功

    //接收数据
    wx.onSocketMessage(function(data) {
      console.log(data);
    })
  },

  quit: function() {
    wx.closeSocket()
    console.log("离线")
    this.setData({
      zt: 'red'
    })
  },

  ontap: function(tapdata) {
    if (this.data.zt == 'red') {
      wx.connectSocket({
        url: "ws://140.143.12.94:8001",
      })
    } 
    if (this.data.zt == 'green') {
      wx.showToast({
        title: '您已经连接！',
        icon: 'success',
        duration: 2000
      })
    }
  },
  tapbuttonred:function(){
    wx.sendSocketMessage({
      data: 'data@1',
    })
  },
    tapbuttongreen: function () {
    wx.sendSocketMessage({
      data: 'data@2',
    })
  },
    tapbuttonblue: function () {
    wx.sendSocketMessage({
      data: 'data@3',
    })
  },
    tapbuttonno: function () {
    wx.sendSocketMessage({
      data: 'data@0',
    })
  }
})