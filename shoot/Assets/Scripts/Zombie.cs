using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class Zombie : MonoBehaviour {
  private new GameObject camera;
  private NavMeshAgent agent;
  private bool stop;
  private enum state { walk,idle,atack }
  private Animator animator;
  void Start() {
    camera = GameObject.Find("Main Camera").gameObject;
    agent = GetComponent<NavMeshAgent>();
    agent.SetDestination(camera.transform.position);
    stop = false;
    animator = GetComponent<Animator>();
  }
  void Update() {
    Vector3 p;
    
    if (!stop && Vector3.Distance(camera.transform.position, this.transform.position) < 2f) {
      animator.SetInteger("state", (int)state.idle);
      p = camera.transform.position;
      p.y = this.transform.position.y;
      transform.LookAt(p);
      agent.isStopped = stop = true;
    }
    else {
      //animator.SetInteger("state", (int)state.walk);
    }
  }
  public void death() {
    //アニメーション無効
    GetComponent<Animator>().enabled = false;
    Invoke("destroyObject", 5f);　//5秒後に実行
    SetKinematic(false);
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
}
