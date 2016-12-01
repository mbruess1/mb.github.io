using UnityEngine;
using System.Collections;

public class InputState : MonoBehaviour {

	public float absoluteVelocityX = 0f;
	public bool standing;
	public float standingThreshold = 1f;
	public bool runButton;

	private Rigidbody2D OtterBody2D;

	void Awake() { //start einmal aufgerufen. Awake jedes mal wenn etwas hinzukommt wärend der laufzeit (Bsp. Feuer einblenden)
		OtterBody2D = GetComponent<Rigidbody2D> ();
	}
	
	// Update is called once per frame
	void Update () {
		runButton = Input.GetMouseButtonDown (0);
	}

	void FixedUpdate () { //Update kann mehrfach aufgerufen werden != FixedUpdate zu einer bestimmten Zeit
		absoluteVelocityX = System.Math.Abs(OtterBody2D.velocity.x);

		if (absoluteVelocityX <= standingThreshold) {
			standing = true;
		} else {
			standing = false;
		}
	}
}
