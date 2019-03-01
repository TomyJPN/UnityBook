using System;
using UnityEngine;

public class Timer : MonoBehaviour {
  public float Interval { get; set; }
  private float elapsed = 0f;
  private bool timerEnabled = true;

  public void ReStart() {
    elapsed = 0f;
    TimerStart();
  }

  public void TimerStart() {
    timerEnabled = true;
  }

  public void TimerStop() {
    timerEnabled = false;
  }

  void Update() {
    if (!timerEnabled) {
      return;
    }

    elapsed += Time.deltaTime;

    if (elapsed >= Interval) {
      Tick.Invoke(this, new EventArgs());
      elapsed = 0f;
    }
  }

  public event EventHandler Tick;
}
