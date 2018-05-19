using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CalcMoveRange : MonoBehaviour {

    // オリジナルマップデータ
    private List<List<int>> mOriginalMapList;

    // 移動計算結果のデータ格納用
    List<List<int>> mResultMoveRangeList;

    //マップ上のx,z位置
    public int mx, mz;

    //移動力
    public int mm;

    //マップの大きさ
    int mxLength = 10;
    int mzLength = 10;

    void Awake()
    {
        // マップデータの作成
       // Mapcreate();
        
    }

    public void Mapcreate() {

        List<int> moveXList = new List<int>();

        for (int k = 0; k < mxLength ; k++)
        {
            moveXList[k] = -1;
        }
        mOriginalMapList.Add(moveXList);
    }

    //探索開始
    //計算結果のマップデータを返す
    public List<List<int>> StartSearch( int currentX, int currentZ, int movePower)
    {
        // mOriginalMapListのコピー作成
        mResultMoveRangeList = new List<List<int>>(mOriginalMapList);

        mxLength = mResultMoveRangeList[0].Count;
        mzLength = mResultMoveRangeList.Count;

        mx = currentX;
        mz = currentZ;
        mm = movePower;

        //現在位置に現在の移動力を代入
        mResultMoveRangeList[mz][mx] = mm;
        Search4(mx, mz, mm);

        return mResultMoveRangeList;
    }

    //移動可能な範囲の4方向を調べる
    void Search4( int x, int z, int m )
    {
        if(0<x && x<mxLength && z< mzLength)
        {
            //上方向
            Search(x, z - 1, m);
            //下方向
            Search(x, z + 1, m);
            //左方向
            Search(x - 1, z, m);
            //右方向
            Search(x + 1, z, m);
        }
    }

    //移動先のセルの調査
    void Search(int x,int z, int m)
    {
        //探索方向のCellがマップエリア領域内かチェック
        if (x < 0 || mxLength <= x) return;
        if (z < 0 || mzLength <= z) return;

        //すでに計算済みのCellかチェック
        if ((m - 1) <= mResultMoveRangeList[z][x]) return;

        m += mOriginalMapList[z][x];

        if (m > 0)
        {
            //進んだ位置に現在の移動力を代入
            mResultMoveRangeList[z][x] = m;
            //移動量があるのでSearch4を再帰呼び出し
            Search4(x, z, m);
        }
        else
        {
            m = 0;
        }

    }

    // Use this for initialization
    void Start () {
        //Debug.Log("%d", mx);
      //  Mapcreate();
    }
	
	// Update is called once per frame
	void Update () {
        
    }
}
