using UnityEngine;
using System.Collections;

public class Goal : MonoBehaviour {

	private InputState inputState;

	void OnTriggerEnter2D (Collider2D other) {
		Time.timeScale = 0;
		Debug.Log ("Win!");
	}
}
