using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class shotCam : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
      getClickObject();
    }
  // 左クリックしたオブジェクトを取得する関数(3D)
  public GameObject getClickObject() {
    GameObject result = null;

    // 左クリックされた場所のオブジェクトを取得
    if (Input.GetMouseButtonDown(0) /*&& !pauseUI.activeSelf*/) {
      //残弾の処理
      /*if (bulletNum == 0) {
        if (reloadVC_flag) {
          //reloadVC.PlayOneShot(reloadVC.clip);  //著作権
          reloadVC_flag = false;
        }
        noBulletSE.PlayOneShot(noBulletSE.clip);
        return result;
      }*/
      //bulletNum--;
      //shotSum++;
      // Debug.Log("shotsum" + shotSum);
      //shotSE.PlayOneShot(shotSE.clip);

      Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
      RaycastHit hit = new RaycastHit();
      if (Physics.SphereCast(ray, 0.01f, out hit)) {
        result = hit.collider.gameObject;
        Debug.Log(result);
        //Instantiate(gunEx, hit.point, Quaternion.identity);   //着弾点にエフェクト
      }
      if (result.gameObject.tag == "enemy") Destroy(result);
    }
    return result;
  }
}
