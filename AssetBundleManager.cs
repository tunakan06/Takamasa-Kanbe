using UnityEngine;
using System;
using System.Collections;

public class AssetBundleManager : MonoBehaviour
{
    // AssetBundleのキャッシュ
    private AssetBundle assetBundleCache;

    // Asset Bundleをロードするコルーチンです
    public IEnumerator LoadAssetBundleCoroutine()
    {
        // Asset BundleのURL
        var url = "";
#if UNITY_ANDROID
        url = "https://www.dropbox.com/home/%E5%85%B1%E6%9C%89%E3%82%B9%E3%83%9A%E3%83%BC%E3%82%B9";
#else
        // url = "http://iOS用catbundleを配置したURL";
#endif

        // ダウンロード処理
        var www = WWW.LoadFromCacheOrDownload(url, 1);
        while (!www.isDone)
        {
            yield return null;
        }

        // TODO エラー処理とか

        // Asset Bundleをキャッシュ
        assetBundleCache = www.assetBundle;

        // リクエストは開放
        www.Dispose();
    }

    // Asset BundleからSpriteを取得します
    public Sprite GetSpriteFromAssetBundle(string assetName)
    {
        try
        {
            return assetBundleCache.LoadAsset<Sprite>(string.Format("{0}.png", assetName));
        }
        catch (NullReferenceException e)
        {
            Debug.Log(e.ToString());
            return null;
        }
    }
}