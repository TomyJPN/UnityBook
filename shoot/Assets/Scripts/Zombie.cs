using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class Zombie : MonoBehaviour {
  private GameObject camera;
  private NavMeshAgent agent;
  private bool stop;
  void Start() {
    camera = GameObject.Find("Main Camera").gameObject;
    agent = GetComponent<NavMeshAgent>();
    agent.SetDestination(camera.transform.position);
    stop = false;
  }
  void Update() {
    if (!stop && Vector3.Distance(camera.transform.position, this.transform.position) < 2f) {
      agent.isStopped = stop = true;
      agent.enabled = false;
    }
  }
  public void death() {
    Invoke("destroyObject", 5f);　//5秒後に実行
  }
  void destroyObject() {
    Destroy(gameObject);  //オブジェクトを消す
  }
}
