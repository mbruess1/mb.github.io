using UnityEngine;
using System.Collections;

public class Follow : MonoBehaviour {

	public Transform player;
	void Update () 
	{
		transform.position = new Vector3 (player.position.x, 0, -10); // Camera follows the player but 6 to the right
	}
}

