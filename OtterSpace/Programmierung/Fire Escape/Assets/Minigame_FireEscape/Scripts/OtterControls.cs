using UnityEngine;
using System.Collections;


public class OtterControls : MonoBehaviour {

	public Vector2 push = new Vector2(50, 0);

	// Update is called once per frame
	void Update () {
		if (Input.GetMouseButtonDown (0)) {
			GetComponent<Rigidbody2D> ().AddForce (push);
		}
	}


}
