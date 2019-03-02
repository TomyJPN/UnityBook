using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class ShotCam : MonoBehaviour {
  public GameObject hitEffect;

  void Update() {
    GameObject clickObject=getClickObject();
    //クリックしたのが敵なら
    if (clickObject!=null && clickObject.gameObject.tag == "enemy") {
      Vector3 vec = clickObject.transform.position - this.transform.position;
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
        Instantiate(hitEffect, hit.point, Quaternion.identity);   //着弾点にエフェクト
      }
      Debug.Log(clickObject);
    }
    return clickObject;
  }
}
