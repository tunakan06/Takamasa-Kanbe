using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerScript : MonoBehaviour {

    Vector3 MOVEX = new Vector3(1.0f, 0, 0); // x軸方向に１マス移動するときの距離
    Vector3 MOVEZ = new Vector3(0, 0, 1.0f); // y軸方向に１マス移動するときの距離

    float x;             // 向き
    float rotationSpeed = 90f;
    float step = 1.0f;   // 移動速度
    public Vector3 target;      // 入力受付時、移動後の位置を算出して保存 
    Vector3 prevPos;     // 何らかの理由で移動できなかった場合、元の位置に戻すため移動前の位置を保存
    bool state;

    CalcMoveRange calcMoveRange = new CalcMoveRange();

    Animator animator;   // アニメーション
    bool enterpush = false;

    //CalcMoveRange cmr;

    // Use this for initialization
    void Start () {
        target = transform.position;
        animator = GameObject.Find("unitychan").GetComponent<Animator>();
    }
	
	// Update is called once per frame
	void Update () {

        // ① 移動中かどうかの判定。移動中でなければ入力を受付
        if (transform.position == target)
        {
            SetTargetPosition();
        }
        Move();
    }

    // ② 入力に応じて移動後の位置を算出
    void SetTargetPosition()
    {

        prevPos = target;

        //if ( > 0)
       // {
       // 移動script
            if (Input.GetKeyDown(KeyCode.RightArrow))
            {
                SetAnimationParam(true);
                target = transform.position + MOVEX;
                transform.rotation = Quaternion.Euler(0, 90.0f, 0);
                //StopAnimationParam();
                //--cmr.mm;
                return;
            }
            if (Input.GetKeyDown(KeyCode.LeftArrow))
            {
                SetAnimationParam(true);
                target = transform.position - MOVEX;
                transform.rotation = Quaternion.Euler(0, -90.0f, 0);
                //StopAnimationParam();
                //--cmr.mm;
                return;
            }
            if (Input.GetKeyDown(KeyCode.UpArrow))
            {
                SetAnimationParam(true);
                target = transform.position + MOVEZ;
                transform.rotation = Quaternion.Euler(0, 0.0f, 0);
                //StopAnimationParam();
                //--cmr.mm;
                return;
            }
            if (Input.GetKeyDown(KeyCode.DownArrow))
            {
                SetAnimationParam(true);
                target = transform.position - MOVEZ;
                transform.rotation = Quaternion.Euler(0, 180.0f, 0);
                //StopAnimationParam();
                //--cmr.mm;
                return;
            }
        // 攻撃スクリプト
        if (Input.GetKeyDown(KeyCode.Return))
        {
            animator.SetBool("Jump", true);
        }
        else
        {
            animator.SetBool("Jump", false);
        }
    }

    // アニメーションセット
    void SetAnimationParam(bool state)
    {
        animator.SetBool("IdletoWalk", state);
       // animator.SetInteger("WalkParam", param);
    }
    // ストップアニメーション
    void StopAnimationParam()
    {
        animator.SetBool("IdletoWalk", false);
        animator.SetBool("toIdle", true);
        // animator.SetInteger("WalkParam", param);
    }

    // ③ 目的地へ移動する
    void Move()
    {
        transform.position = Vector3.MoveTowards(transform.position, target, step * Time.deltaTime);
        //StopAnimationParam();
    }

}
