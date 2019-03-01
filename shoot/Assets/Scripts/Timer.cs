using System;
using UnityEngine;

public class Timer : MonoBehaviour {
  /// <summary>
  /// 時間の間隔[s]
  /// </summary>
  public float Interval { get; set; }

  /// <summary>
  /// 経過時間
  /// </summary>
  private float elapsed = 0f;

  public bool TimerEnabled { get; private set; }
  
  public void ReStart() {
    elapsed = 0f;
    TimerStart();
  }
  
  public void TimerStart() {
    TimerEnabled = true;
  }

  public void TimerStop() {
    TimerEnabled = false;
  }

  /// <summary>
  /// 開始しつつ、時間経過したときのイベントを呼び出す
  /// </summary>
  public void TimerStartAndInvoke() {
    TimerStart();
    Tick.Invoke(this, new EventArgs());
  }

  void Update() {
    if (!TimerEnabled) {
      return;
    }

    elapsed += Time.deltaTime;

    if (elapsed >= Interval) {
      Tick.Invoke(this, new EventArgs());
      elapsed = 0f;
    }
  }

  /// <summary>
  /// 時間が経過したときのイベント
  /// </summary>
  public event EventHandler Tick;
}
