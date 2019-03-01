using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class Zombie : MonoBehaviour {
  private new GameObject camera;
  private NavMeshAgent agent;
  private enum state {walk,idle}  //アニメーションの状態
  private Animator animator;
  private Timer attackTimer;

  void Start() {
    camera = GameObject.Find("Main Camera").gameObject;
    agent = GetComponent<NavMeshAgent>();
    agent.SetDestination(camera.transform.position);  //目標座標を設定
    animator = GetComponent<Animator>();
    SetKinematic(true);  //物理演算を無効にする

    attackTimer = gameObject.AddComponent<Timer>();
    attackTimer.Interval = 3f;
    attackTimer.Tick += AttackTimer_Tick;
    attackTimer.TimerStop();
  }

  private void AttackTimer_Tick(object sender, System.EventArgs e) {
      animator.SetTrigger("attack");
      Invoke("damage", 0.9f);
  }
  
  void Update() {
    //ゾンビが目標点まで2m近づいたら立ち止まる
    if (!attackTimer.TimerEnabled && Vector3.Distance(camera.transform.position, this.transform.position) < 2f) {
      animator.SetInteger("state", (int)state.idle);
      Vector3 p = camera.transform.position;
      p.y = this.transform.position.y;
      transform.LookAt(p);
      agent.isStopped = true;

      attackTimer.TimerStartAndInvoke();
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
  }

  void damage() {
    //ゾンビが死んでいたら無効
    if (agent.enabled) { 
      iTween.ShakePosition(camera, iTween.Hash("x", 0.1f,"y",0.1f, "time", 1f));
    }
  }
}


/*
 public void death() {
    GetComponent<Animator>().enabled = false; //アニメーション無効
    Invoke("destroyObject", 5f);　//5秒後に消滅させる
  }
  void destroyObject() {
    Destroy(gameObject);  //オブジェクトを消す
  }
   */
