using UnityEngine;
using System.Collections;

public class BackgroundScroller : MonoBehaviour {

	public float factor;

	// Use this for initialization
	void Awake () {
		factor = 1.0f / transform.localScale.x;
	}

	// Update is called once per frame
	void Update () {
		GetComponent<MeshRenderer> ().material.SetTextureOffset ("_MainTex", new Vector2 (Camera.main.transform.position.x * factor, 0.0f));
	}


}
