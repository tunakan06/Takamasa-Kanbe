using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TernScript : MonoBehaviour {

    public int playerTurn = 5;

    public float enemyTurn = 0;

    public Text targetText;

    public enum Tern
    {
        UNITY_TURN,
        ENEMY_TURN,

        TURN_NUM,
    }

    public Tern tern;

    string chara;

    // Use this for initialization
    void Start () {

        tern = Tern.UNITY_TURN;
        chara = "Unity";
        this.targetText.text = chara + "'s Turn";
    }
	
	// Update is called once per frame
	void Update () {

        // unity-chanのActionが0の時、enemy-chanのターンに
        if ( playerTurn == 0 && tern == Tern.UNITY_TURN)
        {
            tern = Tern.ENEMY_TURN;
            chara = "Enemy";
            enemyTurn = 5.0f;
        }
        else if( enemyTurn == 0.0f && tern == Tern.ENEMY_TURN)
        {
            tern = Tern.UNITY_TURN;
            chara = "Unity";
            playerTurn = 5;
        }

        this.targetText.text = chara + "'s Turn";
    }
}
