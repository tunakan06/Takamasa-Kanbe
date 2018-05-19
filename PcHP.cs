using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PcHP : MonoBehaviour {

    public Text targetText;
    public readonly int maxHP = 100;        // 体力の最大値
    public int HP;  // 体力
    public int EnemyATK = 10;   // 敵の攻撃力
    //public int playerTurn = 5;

    public TernScript turnScript;

    public enum Phase{
        UNITY_TURN,
        ENEMY_TURN,

        TURN_NUM,
    }

    private bool NewFlag;
    private bool preFlag;
    private Phase phase = Phase.UNITY_TURN;

    Slider unityhpslider;
    TernScript ternScript;

    // Use this for initialization
    private void Start () {
        //hoge();
        HP = maxHP;
        this.targetText = this.GetComponent<Text>();
        this.targetText.text = "Unity-Chan Action:" + turnScript.playerTurn.ToString();
        preFlag = false;
        unityhpslider = GameObject.Find("Slider").GetComponent<Slider>();
        ternScript = GameObject.Find("TernText").GetComponent<TernScript>();
    }

    // Update is called once per frame
    private void Update () {

        NewFlag = Input.GetKeyDown(KeyCode.RightArrow) || Input.GetKeyDown(KeyCode.LeftArrow) || Input.GetKeyDown(KeyCode.UpArrow) || Input.GetKeyDown(KeyCode.DownArrow) || Input.GetKeyDown(KeyCode.Return);

        // ターン数がなくなったら、エネミーターン開始
        //if (turnScript.playerTurn <= 0)
        //{
          //  turnScript.playerTurn = 0;
            //EnemyStart();
        //}

        // 行動の度にターン数を減らす
        if ((preFlag == false) && NewFlag) {
            Turn();
        }

        if (turnScript.playerTurn >= 0)
        {
            this.targetText = this.GetComponent<Text>();
            this.targetText.text = "Unity-Chan Action:" + turnScript.playerTurn.ToString();
        }

        preFlag = NewFlag;

    }

    // ターン数を減らす
    private void Turn()
    {
        turnScript.playerTurn--;
    }

    // エネミーターン開始
    private void EnemyStart()
    {
        phase = Phase.ENEMY_TURN;
    }

}
