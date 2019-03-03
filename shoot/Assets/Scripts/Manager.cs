using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class Manager : MonoBehaviour {
  public Text scoreText;
  public Text lifeText;
  private int life = 2;
  private int score = 0;

  public void scoreUP(int n) {
    score += n;
    scoreText.text = score.ToString();
  }
  public void lifeDown() {
    if(life==1) SceneManager.LoadScene("title");
    life--;
    lifeText.text = "残り"+life.ToString();
  }
}
