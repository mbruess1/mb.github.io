using UnityEngine;
using System.Collections;


public class OtterControls : MonoBehaviour {

	public Vector2 push = new Vector2(150, 1000);
	public float absoluteVelocityX = 0f;
	private Rigidbody2D OtterBody2D;

	private bool IsGrounded = false;

	void OnCollisionStay2D (Collision2D other)
	{
		IsGrounded = true;    
	}
	void OnCollisionEnter2D(Collision2D other)
	{
		IsGrounded = true;    
	}
	void OnCollisionExit2D (Collision2D other)
	{
		IsGrounded = false;    
	}
		

	void Awake() { //start einmal aufgerufen. Awake jedes mal wenn etwas hinzukommt wärend der laufzeit (Bsp. Feuer einblenden)
		OtterBody2D = GetComponent<Rigidbody2D> ();

	}

	// Update is called once per frame
	void Update ()
	{
		if (Input.GetMouseButtonDown (0) && IsGrounded) {
			OtterBody2D.AddForce (push);
		}
	}
}