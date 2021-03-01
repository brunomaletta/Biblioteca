# Biblioteca

Biblioteca de algoritmos, estruturas de dados e primitivas para maratona de programação do time [UFMG] Rábalabaxúrias (Bruno, Rafael & Papa).

Códigos em C++, em maior parte implementados pelos integrantes do time.

#### PDF

Versão em PDF (provavelmente não atualizada) dos algoritmos pode ser encontrada [aqui](https://github.com/brunomaletta/Biblioteca/blob/master/latex/biblioteca.pdf).

O *theoretical* (documento com teoremas, identidades e informações teóricas relevantes) pode ser encontrado [aqui](https://github.com/brunomaletta/Biblioteca/blob/master/latex/theoretical.pdf).

## Conteúdo

### Programação Dinâmica

- [Convex Hull Trick](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/DP/CHT.cpp)
- [Divide and Conquer DP](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/DP/DC-DP.cpp)
- [Longest Common Subsequence - O(n+m) de memória](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/DP/lcs.cpp)
- [Mochila - O(n+cap) de memória](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/DP/mochila.cpp)
- [SOS DP](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/DP/sosdp.cpp)

### Estruturas de Dados

- Segment Tree
    - [Segtree Padrão (soma)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SegTree/SegTree.cpp)
    - [Segtree 2D (iterativa)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SegTree/SegTree2D.cpp)
    - [Segtree Beats](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SegTree/SegTreeBeats.cpp)
    - [Segtree Colorida (lê os comentários pra saber o que faz)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SegTree/SegTreeColor.cpp)
    - [Segtree Esparsa - Lazy](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SegTree/SegTreeEsparsa.cpp)
    - [Segtree Esparsa - O(q) Memória](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SegTree/SegTreeEsparsa2.cpp)
    - [Segtree Iterativa](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SegTree/SegTreeIterativa.cpp)
    - [Segtree Iterativa com Lazy Propagation](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SegTree/SegTreeIterativaComLazy.cpp)
    - [Segtree de PA](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SegTree/SegTreePA.cpp)
    - [Segtree Persistente](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SegTree/SegTreePersistent.cpp)
- [BIT (Fenwick Tree)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/BIT.cpp)
- [BIT com Soma em Range](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/BIT-range.cpp)
- [DSU](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/dsu.cpp)
- [DSU Persistente](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/DSUPersistente.cpp)
- [Order Statistic Set (GCC)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/OrderStatisticSet.cpp)
- [SQRT-decomposition](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SQRT-decomposition.cpp)
- [Sparse Table](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SparseTable.cpp)
- [Sparse Table Disjunta](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SparseTableDisjunta.cpp)
- [Wavelet Tree](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/WaveletTree.cpp)
- [MergeSort Tree](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/mergeSortTree.cpp)
- [Minqueue - Deque](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/minqueueDeque.cpp)
- [Minqueue - Stack](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/minqueueStack.cpp)
- [RMQ <O(n), O(1)>](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/rmq.cpp)
- [RMQ <O(n), O(1)> - Cartesian Tree](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/rmq2.cpp)
- [Splaytree](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/splaytree.cpp)
- [Splaytree Implicita](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/splaytreeImplicita.cpp)
- [Split-Merge Set](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/splitMergeSet.cpp)
- [Split-Merge Set - Lazy](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/splitMergeSetLazy.cpp)
- [SQRT Tree](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/sqrtTree.cpp)
- [Treap](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/treap.cpp)
- [Treap Implícita](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/treapImplicita.cpp)
- [Treap Implícita Persistente](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/treapPersistent.cpp)

### Grafos

- LCA/HLD
    - [Heavy-Light Decomposition - Aresta](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/LCA-HLD/HLD-aresta.cpp)
    - [Heavy-Light Decomposition - Vértice](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/LCA-HLD/HLD-vertice.cpp)
    - [Heavy-Light Decomposition sem Update](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/LCA-HLD/HLDsemUpdate.cpp)
    - [LCA <O(n), O(1)>](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/LCA-HLD/LCA.cpp)
    - [LCA com Binary Lifting](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/LCA-HLD/LCAcomBinaryLifting.cpp)
    - [LCA com HLD](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/LCA-HLD/LCAcomHLD.cpp)
- LCT
    - [Link-cut Tree - Aresta](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/LCT/lct-aresta.cpp)
    - [Link-cut Tree - Vertice](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/LCT/lct-vertice.cpp)
    - [Link-cut Tree Padrão](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/LCT/lct.cpp)
- [Tarjan - Pontes e Pontos de Articulação](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/ArtPoint.cpp)
- [Bellman-Ford](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/BellmanFord.cpp)
- [Dominator Tree](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/DominatorTree.cpp)
- [Floyd-Warshall](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/FloydWarshall.cpp)
- [Blossom](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/blossom.cpp)
- [Centro/Diâmetro em Árvore](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/center.cpp)
- [Centroid decomposition](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/centroid-decomp.cpp)
- [Centroid (encontra os centroids da árvore)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/centroid.cpp)
- [Dijkstra](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/dijkstra.cpp)
- [Dinic](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/dinic.cpp)
- [AGM Direcionada (arborescência)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/directedMST.cpp)
- [Euler Path / Euler Cycle Linear](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/eulerPath.cpp)
- [Euler Tour Tree](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/eulerTourTree.cpp)
- [Kosaraju](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/kosaraju.cpp)
- [Kruskal](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/kruskal.cpp)
- [Kuhn](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/kuhn.cpp)
- [Line Tree](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/linetree.cpp)
- [Max Flow com Lower Bound](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/lowerBoundMaxFlow.cpp)
- [MinCost-MaxFlow](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/minCostMaxFlow.cpp)
- [Prufer Code Linear](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/prufer.cpp)
- [Sack (DSU em árvores)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/sack.cpp)
- [Tarjan - SCC e Componentes Biconexas](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/tarjan.cpp)
- [Topological Sort](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/topo_sort.cpp)
- [Isomorfismo de Árvores](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/treeIsomorf.cpp)
- [Virtual Tree](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/virtualTree.cpp)

### Matemática

- [2-SAT (com recuperação)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/2SAT.cpp)
- [Logaritmo Discreto](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/Baby-step-giant-step.cpp)
- [Miller-Rabin](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/MillerRabin.cpp)
- [Inverso Modular](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/ModInverse.cpp)
- [Teorema Chines do Resto](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/chinese.cpp)
- [FFT](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/convolution.cpp)
- [Crivo de Eratosthenes Linear (e variações)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/crivo.cpp)
- [Detecção de Ciclo - Tortoise and Hare](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/cycleDetection.cpp)
- [Divisão de Polinomios (naive)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/divPol.cpp)
- [Exponenciação Rápida](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/fastPow.cpp)
- [Eliminação Gaussiana](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/gauss.cpp)
- [Eliminação Gaussiana de XOR](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/gaussXor.cpp)
- [Karatsuba](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/karatsuba.cpp)
- [Algoritmo de Euclides](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/mdc.cpp)
- [Algoritmo de Euclides Estendido](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/mdcEstendido.cpp)
- [Mulmod O(1)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/mulmod.cpp)
- [Ordem de Elemento do Grupo](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/ordemGrupo.cpp)
- [Algoritmo Rho de Pollard (Pollard Rho)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/pollardrho.cpp)
- [Distribuição Binomial](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/probability_binomial.cpp)
- [Totiente](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/totiente.cpp)

### Primitivas

- [Big Integer - C++](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Primitivas/bigint.cpp)
- [Números Complexos](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Primitivas/complex.cpp)
- [Primitivas Geométricas](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Primitivas/geometria.cpp)
- [Primitivas Geométricas Inteiras](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Primitivas/geometriaInt.cpp)
- [Primitivas Geométricas 3D](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Primitivas/geometria3D.cpp)
- [Primitivas de Matriz - Exponenciação](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Primitivas/matrix.cpp)
- [Aritmética Modular](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Primitivas/modularArithmetic.cpp)
- [Primitivas de Polinômios](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Primitivas/poly.cpp)

### Strings

- [Suffix Array O(n)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/SuffixArray.cpp)
- [Suffix Array O(n log n)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/SuffixArray2.cpp)
- [Trie](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/Trie.cpp)
- [Aho-corasick](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/ahocorasick.cpp)
- [Aho-corasick - Autômato](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/ahocorasickAutomaton.cpp)
- [eertree (Palindromic Tree)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/eertree.cpp)
- [String Hashing](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/hashing.cpp)
- [String Hashing - módulo 2^61 - 1](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/hashingLargeMod.cpp)
- [KMP](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/kmp.cpp)
- [Manacher](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/manacher.cpp)
- [Max Suffix (lexicográfico) O(n)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/maxSuffix.cpp)
- [Autômato de Sufixo](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/suffixAutomaton.cpp)
- [Algoritmo Z](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/z.cpp)

### Problemas

- [Area Máxima de Histograma](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/AreaHistograma.cpp)
- [Inversion Count](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/InversionCount.cpp)
- [RMQ Offline com Divide and Conquer](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/RMQoffline.cpp)
- [Área da Uniao de Retangulos](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/areaUniaoRetangulo.cpp)
- [Arpa's Trick](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/arpa.cpp)
- [Coeficiente Binomial Modular (para valores grandes e mod não tão grande)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/binomial.cpp)
- [Closest Pair of Points](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/closestPairOfPoints.cpp)
- [Conectividade Dinâmica - DSU](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/conectividadeDinamica.cpp)
- [Conectividade Dinâmica - LCT](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/conectividadeDinamica2.cpp)
- [Distinct Range Query - Wavelet](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/distinct.cpp)
- [Distinct Range Query - Persistent Segtree](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/distinct2.cpp)
- [Distinct Range Query com Update](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/distinctUpdate.cpp)
- [Dominator Points](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/dominatorPoints.cpp)
- [Triângulos em Grafos](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/graphTriangles.cpp)
- [Gray Code](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/grayCode.cpp)
- [Algoritmo Húngaro (assignment)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/hungarian.cpp)
- [Coloração de Grafo de Intervalo](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/intervalGraphColoring.cpp)
- [Conjunto Independente Máximo com Peso em Grafo de Intervalo](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/intervalGraphIndSet.cpp)
- [Longest Increasing Subsequence (recuperando)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/lis.cpp)
- [Longest Increasing Subsequence (tamanho)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/lis2.cpp)
- [Min Fixed Range](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/min-fixed-range.cpp)
- [Mininum Enclosing Circle O(n)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/minCirc.cpp)
- [MO](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/mo.cpp)
- [MO - DSU](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/mo-dsu.cpp)
- [MO em Árvores](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/moOnTrees.cpp)
- [Nim](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/nim.cpp)
- [Pontos Dentro de Polígono](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/pointsInsidePol.cpp)
- [Interseção de Segmentos](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/segmentIntersection.cpp)
- [Verificação de Polígono Simples](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/simplePolygon.cpp)
- [Sweep Direction](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/sweepDirection.cpp)

### Extra

- [Debug](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Extra/debug.cpp)
- [fastIO](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Extra/fastIO.cpp)
- [makefile](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Extra/makefile)
- [rand](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Extra/rand.cpp)
- [Stresstest](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Extra/stress.sh)
- [Template C++](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Extra/template.cpp)
- [vimrc](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Extra/vimrc)
