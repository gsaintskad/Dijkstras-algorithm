#include<iostream>
#include<vector>

using namespace std;

const int INF = 9999;

struct edge {
	int weight;
	int indexTo;
};
struct Node
{
	int id;
	vector<edge> edges;

	int prevIndex;
	int wieght = INF;
	bool isVisited = false;
	void visited() {
		isVisited = true;
	}
};


Node setnode(vector<Node>q) {
	Node n = q[0];
	for (int i = 0; i < q.size(); i++) {
		if (n.wieght > q[i].wieght && !n.isVisited) {
			n = q[i];
		}
	}
	return n;
}
int ercheck(vector<Node>Q, Node w) {
	for (int i = 0; i < Q.size(); i++) {
		if (w.id == Q[i].id) return i;
	}
}
vector<Node> graphedit(vector<Node> G, Node w) {
	for (int i = 0; i < G.size(); i++) {
		if (w.id == G[i].id) {
			G[i] = w;
			break;
		}
	}
	return G;
}
vector<Node> Dijkstra(vector<Node> G) {
	vector<Node> Q;
	Q.push_back(G[0]);
	// MAIN CODE

	while (Q.size()) {
		//node setter
		Node w = setnode(Q);
		//Queue flowing
		for (int i = 0; i < w.edges.size(); i++) {
			for (int j = 0; j < G.size(); j++) {
				if (w.edges[i].indexTo == G[j].id) {
					for (int k = 0; k < Q.size(); k++) {
						if (Q[k].id == G[j].id || G[j].isVisited == true) {
							break;
						}
						else if (k == Q.size() - 1) { Q.push_back(G[j]); break; }
					}
					break;
				}
			}
		}
		Q.erase(Q.begin() + ercheck(Q, w));
		w.visited();
		for (int i = 0; i < w.edges.size(); i++) {
			for (int j = 0; j < Q.size(); j++) {
				if (Q[j].id == w.edges[i].indexTo) {
					if (Q[j].wieght > w.wieght + w.edges[i].weight) {
						Q[j].prevIndex = w.id;
						Q[j].wieght = w.wieght + w.edges[i].weight;
					}
					break;
				};
			}
		}
		G = graphedit(G, w);
	}

	int error = 0;
	for (int i = 0; i < G.size(); i++) {
		if (G[i].isVisited == false) {
			error++;
			break;
		}
	}
	if (!error) return G;

}

void print(vector<Node>G) {
	for (int i = 0; i < G.size(); i++) {
		cout << "\tID : " << G[i].id << " ;\tWEIGHT : " << G[i].wieght
			<< " ;\tPREVIOUS ID : " << G[i].prevIndex << " ;" << endl;
	}
}
int main() {
	Node a, b, c, d, e, f, g;
	//a node
	a.id = 1;
	a.edges = { (2,3),{10,4} };
	a.wieght = 0;

	//b node
	b.id = 2;
	b.edges = { {1,4},{1,6} };

	//c node

	c.id = 3;
	c.edges = { {1,2},{5,6},{4,5} };

	//d node
	d.id = 4;
	d.edges = { {1,7},{2,1} };

	//e node
	e.id = 5;
	e.edges = { {1,6} };

	//f node

	f.id = 6;
	f.edges = { {5,3},{2,7} };

	//g node 

	g.id = 7;
	g.edges = { {3,2} };

	vector<Node> G;
	G = { a,b,c,d,e,f,g };


	G = Dijkstra(G);

	print(G);
	//Second GRAPH
	cout << "\tSecond Graph :\n\n";
	Node z, x, k, v, n, m;
	//z node
	z.id = 1;
	z.edges = { {3,2},{1,3 },{3,4} };
	z.wieght = 0;
	//x node
	x.id = 2;
	x.edges = { {3,1},{4,3} };
	//k node
	k.id = 3;
	k.edges = { {1,1},{4,2},{7,5},{5,6} };
	//v node
	v.id = 4;
	v.edges = { {3,1},{2,6} };
	//n node;
	n.id = 5;
	n.edges = { {7,3},{4,6} };
	//m node;
	m.id = 6;
	m.edges = { {2,4},{5,3},{4,5} };

	vector<Node> G1;
	G1 = { z, x, k, v, n, m };
	G1 = Dijkstra(G1);
	print(G1);

}