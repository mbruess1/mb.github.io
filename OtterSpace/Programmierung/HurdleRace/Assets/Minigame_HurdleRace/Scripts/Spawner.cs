using UnityEngine;
using System.Collections;

public class Spawner : MonoBehaviour {

	public GameObject[] prefab;
	public float waitSeconds;


	void Start(){
		StartCoroutine (FireSpawn());
		waitSeconds = 0f;
	}
	void Update() {
		waitSeconds = Random.Range(3.5f, 6.0f);
	}

	IEnumerator FireSpawn (){
		yield return new WaitForSeconds (waitSeconds);

		int prefabIndex = Random.Range (0, prefab.Length);

		Vector3 prefabPosition = new Vector3 (transform.position.x, prefab [prefabIndex].transform.position.y, transform.position.z);

		Instantiate (prefab [prefabIndex], prefabPosition, prefab[prefabIndex].transform.rotation);

		StartCoroutine (FireSpawn());
	}
}

//public static int scoreValue = Random.Range (1000, 1500);
//You can't use Random.Range as an initializer for a static variable. Add an Awake or Start method and initialize scoreValue there. 
//Or if there isn't a compelling reason for it to be static, remove static.
//
//	ArgumentException: Range can only be called from the main thread.
//	Constructors and field initializers will be executed from the loading thread when loading a scene.
//	Don't use this function in the constructor or field initializers, instead move initialization code to the Awake or Start function.