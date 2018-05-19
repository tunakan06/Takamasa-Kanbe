using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class SceneController : MonoBehaviour
{
    public AssetBundleManager assetBundleManager;
    public Image image;

    public IEnumerator Start()
    {
        // Asset Bundleのロード処理
        yield return StartCoroutine(assetBundleManager.LoadAssetBundleCoroutine());
        // ロード完了後、Assetが取り出せるようになる
        image.sprite = assetBundleManager.GetSpriteFromAssetBundle("cat");
    }
}