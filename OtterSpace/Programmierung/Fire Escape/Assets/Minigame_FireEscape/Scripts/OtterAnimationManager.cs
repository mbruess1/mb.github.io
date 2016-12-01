using UnityEngine;
using System.Collections;

public class OtterAnimationManager : MonoBehaviour {

	private Animator animator;
	private InputState inputState; //InputState muss mit .cs übereinstimmen

	void Awake() { //start einmal aufgerufen. Awake jedes mal wenn etwas hinzukommt wärend der laufzeit (Bsp. Feuer einblenden)
		animator = GetComponent<Animator> ();
		inputState = GetComponent<InputState> ();
	}


	// Update is called once per frame
	void Update () {
		animator.SetBool ("Standing", inputState.standing);
	}
}
