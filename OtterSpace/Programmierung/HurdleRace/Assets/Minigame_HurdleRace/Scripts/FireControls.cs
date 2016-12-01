using UnityEngine;
using System.Collections;

public class FireControls : MonoBehaviour {

	public Vector2 push = new Vector2(-125, 0);

	// Update is called once per frame
	void Start () {
		
		GetComponent<Rigidbody2D> ().AddForce (push);

	}

	void OnTriggerEnter2D (Collider2D other) {
		if (other.gameObject.name == "Otter") {
			Time.timeScale = 0;
			Debug.Log ("Game Over!");
		}
	}
}
