using UnityEngine;
using System.Collections;

public class Goal : MonoBehaviour {

	private InputState inputState;

	void OnTriggerEnter2D (Collider2D coll) {
		if (coll.gameObject.name == "Otter") {
			Time.timeScale = 0;
			Debug.Log ("Win!");
		}
	}
}
