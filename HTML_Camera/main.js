
var connection = new WebSocket('ws://'+location.hostname+':81/', ['arduino']);

connection.onopen = function () {
    connection.send('Connect ' + new Date());
};
connection.onerror = function (error) {
    console.log('WebSocket Error ', error);
};
connection.onmessage = function (e) {
    console.log('Server: ', e.data);
};
connection.onclose = function(){
    console.log('WebSocket connection closed');
};

function Func_mod() {
    var Btn = document.getElementById("Btn_modalita");
    var Mod_S = document.getElementById("Semplice");
    var Mod_A = document.getElementById("Avanzata");

    if(Mod_A.style.display === "inline")
    {
      Mod_A.style.display = "none";
      Btn.innerHTML = "Semplice";
      Btn.style.color = "#000000";
      Btn.style.backgroundColor = "#FFFFFF";

    }
    else
    {
      Mod_A.style.display = "inline";
      Btn.innerHTML = "Avanzata";
      Btn.style.color = "#FFFFFF";
      Btn.style.backgroundColor = "#00857C";
    }
}

function Cambia_pagina(page) {
    var Debug = document.getElementById("debug");
    Debug.innerHTML = page;
    connection.send(page);
}

function Send_Shoot(ind) {
    var Debug = document.getElementById("debug");
    var T_focus = document.getElementById('t_fuoco').value;
    var T_shoot = document.getElementById('t_scatto').value;
    var Time_f = document.getElementById('tempo_f').value;
    var Time_s = document.getElementById('tempo_s').value;

    if(T_focus > 9999)
    {
      T_focus.value = 9999;
    }

    if(T_shoot > 9999)
    {
      T_shoot.value = 9999;
    }

    if(ind == "0") //FS
    {
      var head = "FS";
      var bottom = Time_s;

      if(1 <= T_shoot && T_shoot <= 9)//Millisecondi
      {
        var center = T_shoot;
        var linee = "---";
      }
      else if(10 <= T_shoot && T_shoot <= 99)//Secondi
      {
        var center = T_shoot;
        var linee = "--";
      }
      else if(100 <= T_shoot && T_shoot <= 999)//Minuti
      {
        var center = T_shoot;
        var linee = "-";
      }
      else if(1000 <= T_shoot && T_shoot <= 9999)//Minuti
      {
        var center = T_shoot;
        var linee = "";
      }
      else
      {
        var center = "";
        var linee = "----";
      }
    }

    else if(ind == "1") //FF
    {
      var head = "FF";
      var bottom = Time_f;

      if(1 <= T_focus && T_focus <= 9)//Millisecondi
      {
        var center = T_focus;
        var linee = "---";
      }
      else if(10 <= T_focus && T_focus <= 99)//Secondi
      {
        var center = T_focus;
        var linee = "--";
      }
      else if(100 <= T_focus && T_focus <= 999)//Minuti
      {
        var center = T_focus;
        var linee = "-";
      }
      else if(1000 <= T_focus && T_focus <= 9999)//Minuti
      {
        var center = T_focus;
        var linee = "";
      }
      else
      {
        var center = "";
        var linee = "----";
      }
    }

    else if(ind == "2") //SS
    {
      var head = "SS";
      var bottom = Time_s;

      if(1 <= T_shoot && T_shoot <= 9)//Millisecondi
      {
        var center = T_shoot;
        var linee = "---";
      }
      else if(10 <= T_shoot && T_shoot <= 99)//Secondi
      {
        var center = T_shoot;
        var linee = "--";
      }
      else if(100 <= T_shoot && T_shoot <= 999)//Minuti
      {
        var center = T_shoot;
        var linee = "-";
      }
      else if(1000 <= T_shoot && T_shoot <= 9999)//Minuti
      {
        var center = T_shoot;
        var linee = "";
      }
      else
      {
        var center = "";
        var linee = "----";
      }
    }

    var Tempo_finale = head + center + linee + bottom + "*";

    Debug.innerHTML = Tempo_finale;
    connection.send(Tempo_finale);
}
