using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spawner : MonoBehaviour {
  public GameObject zombie;
  [Range(1,2000)]
  public int probability = 100;
  void Update() {
    if (Random.Range(1, probability) == 1) {
      spawn();
    }
  }

  void spawn() {
    GameObject.Instantiate(zombie, this.transform.position, Quaternion.identity);
  }
}
