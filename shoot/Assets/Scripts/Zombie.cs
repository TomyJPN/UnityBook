using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Zombie : MonoBehaviour {
  void Start() {

  }
  void Update() {

  }
  public void death() {
    Invoke("destroyObject", 5f);　//5秒後に実行
  }
  void destroyObject() {
    Destroy(gameObject);  //オブジェクトを消す
  }
}
