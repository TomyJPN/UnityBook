using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class Zombie : MonoBehaviour {
  public void death() {
    Destroy(gameObject);  //オブジェクトを消す
  }
  void destroyObject() {
    Destroy(gameObject);  //オブジェクトを消す
  }
  /*
  private new GameObject camera;
  private NavMeshAgent agent;
  private bool stop;
  private enum state { walk,idle,atack }  //アニメーションの状態
  private Animator animator;
  void Start() {
    camera = GameObject.Find("Main Camera").gameObject;
    agent = GetComponent<NavMeshAgent>();
    agent.SetDestination(camera.transform.position);  //目標座標を設定
    stop = false;
    animator = GetComponent<Animator>();
  }
  void Update() {
    //ゾンビが目標点まで2m近づいたら立ち止まる
    if (!stop && Vector3.Distance(camera.transform.position, this.transform.position) < 2f) {
      animator.SetInteger("state", (int)state.idle);
      Vector3 p = camera.transform.position;
      p.y = this.transform.position.y;
      transform.LookAt(p);
      agent.isStopped = stop = true;
    }
    else {
      //animator.SetInteger("state", (int)state.walk);
    }
  }
  //死ぬ処理
  public void death() {
    GetComponent<Animator>().enabled = false; //アニメーション無効
    Invoke("destroyObject", 5f);　//5秒後に消滅させる
    SetKinematic(false);  //物理演算を付ける
    agent.enabled = false;
  }
  void destroyObject() {
    Destroy(gameObject);  //オブジェクトを消す
  }

  public void SetKinematic(bool newValue) {
    Component[] components = GetComponentsInChildren(typeof(Rigidbody));
    foreach (Component c in components) {
      (c as Rigidbody).isKinematic = newValue;
    }
  }*/
}
