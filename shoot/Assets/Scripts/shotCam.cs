using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShotCam : MonoBehaviour {
  void Start() {

  }
  void Update() {
    GameObject clickObject=getClickObject();
    if (clickObject!=null && clickObject.gameObject.tag == "enemy") {
      clickObject.transform.root.GetComponent<Animator>().enabled = false;
      //clickObject.GetComponent<Rigidbody>().AddForce(new Vector3(1000f,0,0));
      Vector3 vec = clickObject.transform.position - this.transform.position;
      clickObject.GetComponent<Rigidbody>().velocity = vec.normalized*10;
    }
  }
  // 左クリックしたオブジェクトを取得する関数
  public GameObject getClickObject() {
    GameObject clickObject = null;
    if (Input.GetMouseButtonDown(0)) {
      Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
      RaycastHit hit = new RaycastHit();
      if (Physics.SphereCast(ray, 0.1f, out hit)) {
        clickObject = hit.collider.gameObject;
      }
    }
    return clickObject;
  }
}

/*
 // 左クリックしたオブジェクトを取得する関数(3D)
  public GameObject getClickObject() {
    GameObject result = null;

    // 左クリックされた場所のオブジェクトを取得
    if (Input.GetMouseButtonDown(0) && !pauseUI.activeSelf) {
      //残弾の処理
      if (bulletNum == 0) {
        if (reloadVC_flag) {
          //reloadVC.PlayOneShot(reloadVC.clip);  //著作権
          reloadVC_flag = false;
        }
        noBulletSE.PlayOneShot(noBulletSE.clip);
        return result;
      }
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
   */