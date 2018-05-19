using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class EnemyHP : MonoBehaviour {

    public Text targetText;
    public readonly float maxEnemyHP = 15.0f;        // 体力の最大値
    float enemyHP;

    public Vector3 playerPos;
    public Vector3 enemyPos;
    float   dis;
    public Vector3 target;      // 入力受付時、移動後の位置を算出して保存

    bool NewFlag;
    bool preFlag;

    int i = 0;

    Slider enemyhpslider;
    Animator enemyanim;
    TernScript ternScript;
    //PcHP pcHP;
    //PlayerScript playerScript;

    private bool actNewFlag;
    private bool actPreFlag;
    PlayerScript playerScript;

    // Use this for using UnityEngine.UI;initialization
    void Start()
    {
        playerScript = GameObject.Find("unitychan").GetComponent<PlayerScript>();
        enemyHP = maxEnemyHP;
        // Flag1 = true;
        enemyhpslider = GameObject.Find("enemyHPBar").GetComponent<Slider>();
        preFlag = false;
        enemyanim = GameObject.Find("SapphiArtchan").GetComponent<Animator>();
        enemyanim.SetBool("param_idletoko_big", false);
        //enemyanim.SetBool("param_idletodamage", false);
        ternScript = GameObject.Find("TernText").GetComponent<TernScript>();
        target = transform.position;
        actPreFlag = false;
    }

    // Update is called once per frame
    void Update()
    {
        NewFlag = Input.GetKeyDown(KeyCode.Return);
        // 行動の度にターン数を減らす
        if ((actPreFlag == false) && NewFlag)
        {
            Turn();
            Debug.Log(ternScript.enemyTurn);
        }

        if (ternScript.enemyTurn >= 0.0f)
        {
            this.targetText = this.GetComponent<Text>();
            this.targetText.text = "enemy-Chan Action:" + ternScript.enemyTurn.ToString();
        }

        playerPos = GameObject.Find("unitychan").transform.position;
        enemyPos = GameObject.Find("SapphiArtchan").transform.position;
        dis = Vector3.Distance(playerPos, enemyPos);

        if ( (preFlag == false) && NewFlag && (dis <= 1.0f) )
        {
            enemyhpslider.value = enemyhpslider.value - 0.5f;
            Debug.Log(enemyhpslider.value);
            //NewFlag = Input.GetKey(KeyCode.Return);
            enemyanim.SetBool("param_idletodamage", true);

        }
        else
        {
            enemyanim.SetBool("param_idletodamage", false);
        }
        if(enemyhpslider.value == 0.0f)
        {
            enemyanim.SetBool("param_idletoko_big", true);
        }
        preFlag = NewFlag;
    }


    // ターン数を減らす
    private void Turn()
    {
        wait();
        ternScript.enemyTurn = ternScript.enemyTurn - 1.0f;
    }

    IEnumerator wait()
    {
        yield return new WaitForSeconds(10);
    }

}

