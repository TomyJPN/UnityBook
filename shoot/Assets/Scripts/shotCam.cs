using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class ShotCam : MonoBehaviour {
  void Start() {
  }
  void Update() {
    GameObject clickObject=getClickObject();
    //クリックしたのが敵なら
    if (clickObject!=null && clickObject.gameObject.tag == "enemy") {
      //アニメーション無効
      clickObject.transform.root.GetComponent<Animator>().enabled = false;  
      Vector3 vec = clickObject.transform.position - this.transform.position;
      //clickObject.transform.root.GetComponent<NavMeshAgent>().enabled = false;
      //射撃した部位に力を加える
      clickObject.GetComponent<Rigidbody>().velocity = vec.normalized*15;
      //ゾンビ側のスクリプトのdeath()呼び出し
      clickObject.transform.root.GetComponent<Zombie>().death();  
    }
  }
  // 左クリックしたオブジェクトを取得する関数
  public GameObject getClickObject() {
    GameObject clickObject = null;
    if (Input.GetMouseButtonDown(0)) {  //左クリック
      Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
      RaycastHit hit = new RaycastHit();
      if (Physics.SphereCast(ray, 0.1f, out hit)) {
        clickObject = hit.collider.gameObject;
      }
      Debug.Log(clickObject);
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