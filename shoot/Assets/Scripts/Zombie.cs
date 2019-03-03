using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class Zombie : MonoBehaviour {
  private new GameObject camera;
  private NavMeshAgent agent;
  private bool stop;
  private enum state { walk, idle }  //アニメーションの状態
  private Animator animator;
  private float timeOut;
  private float timeElapsed;
  Manager manager;

  void Start() {
    camera = GameObject.Find("Main Camera").gameObject;
    agent = GetComponent<NavMeshAgent>();
    agent.SetDestination(camera.transform.position);  //目標座標を設定
    stop = false;
    animator = GetComponent<Animator>();
    SetKinematic(true);  //物理演算を無効にする
    timeOut = 3f;
    manager = GameObject.Find("Manager").GetComponent<Manager>();
  }
  void Update() {
    timeElapsed += Time.deltaTime;
    if (timeElapsed >= timeOut && stop) {
      animator.SetTrigger("attack");
      timeElapsed = 0.0f;
      Invoke("damage", 0.9f);
    }

    //ゾンビが目標点まで2m近づいたら立ち止まる
    if (stop ||
        Vector3.Distance(camera.transform.position, this.transform.position) >= 2f) {
      return;
    }
    animator.SetInteger("state", (int)state.idle);
    Vector3 p = camera.transform.position;
    p.y = this.transform.position.y;
    transform.LookAt(p);
    agent.isStopped = stop = true;
  }
  //死ぬ処理
  public void death() {
    if (!agent.enabled) return;
    GetComponent<Animator>().enabled = false; //アニメーション無効
    Invoke("destroyObject", 5f);　//5秒後に消滅させる
    SetKinematic(false);  //物理演算を付ける
    agent.enabled = false;
    manager.scoreUP(100);
  }
  void destroyObject() {
    Destroy(gameObject);  //オブジェクトを消す
  }

  public void SetKinematic(bool newValue) {
    Component[] components = GetComponentsInChildren(typeof(Rigidbody));
    foreach (Component c in components) {
      (c as Rigidbody).isKinematic = newValue;
    }
  }

  void damage() {
    if (!agent.enabled) {
      return;       //ゾンビが死んでいたら無効
    }
    iTween.ShakePosition(camera, iTween.Hash("x", 0.1f, "y", 0.1f, "time", 1f));
    manager.lifeDown();
  }
}