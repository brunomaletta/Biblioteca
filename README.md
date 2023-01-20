# Biblioteca

Biblioteca de algoritmos, estruturas de dados e primitivas para Maratona de Programação da UFMG.

Códigos em C++, em maior parte implementados pelos alunos da universidade.

#### PDF

Versão em PDF (provavelmente não atualizada) dos algoritmos pode ser encontrada [aqui](https://github.com/brunomaletta/Biblioteca/blob/master/pdf/biblioteca.pdf).

Para atualizar o PDF primeiro instale o latex executando 
```
sudo apt install texlive-full
sudo apt install rubber
```
e então execute `./getlatex.sh` na pasta latex.


O *theoretical guide* (documento com teoremas, identidades e informações teóricas relevantes) pode ser encontrado [aqui](https://github.com/brunomaletta/Biblioteca/blob/master/pdf/theoretical.pdf).

## Conteúdo

### Programação Dinâmica

- [Convex Hull Trick](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/DP/CHT.cpp)
- [Convex Hull Trick - Dinâmico](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/DP/CHT-Dinamico.cpp)
- [Divide and Conquer DP](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/DP/DC-DP.cpp)
- [Longest Common Subsequence - O(n+m) de memória](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/DP/lcs.cpp)
- [Mochila - O(n+cap) de memória](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/DP/mochila.cpp)
- [SOS DP](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/DP/sosdp.cpp)

### Estruturas de Dados

- Segment Tree
    - [Segtree Padrão (soma)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SegTree/SegTree.cpp)
    - [Segtree 2D (iterativa)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SegTree/SegTree2D.cpp)
    - [Segtreap (equivalente a seg 2D esparsa)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SegTree/SegTreap.cpp)
    - [Segtree Beats](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SegTree/SegTreeBeats.cpp)
    - [Segtree Colorida (lê os comentários pra saber o que faz)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SegTree/SegTreeColor.cpp)
    - [Segtree Esparsa - Lazy](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SegTree/SegTreeEsparsa.cpp)
    - [Segtree Esparsa - O(q) Memória](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SegTree/SegTreeEsparsa2.cpp)
    - [Segtree Iterativa](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SegTree/SegTreeIterativa.cpp)
    - [Segtree Iterativa com Lazy Propagation](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SegTree/SegTreeIterativaComLazy.cpp)
    - [Segtree de PA](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SegTree/SegTreePA.cpp)
    - [Segtree Persistente](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SegTree/SegTreePersistent.cpp)
- [BIT (Fenwick Tree)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/BIT.cpp)
- [BIT 2D](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/BIT2D.cpp)
- [BIT com Soma em Range](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/BIT-range.cpp)
- [BIT-Sort Tree](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/bitSortTree.cpp)
- [DSU (e variações)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/dsu.cpp)
- [Li-Chao Tree](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/lichao.cpp)
- [MergeSort Tree](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/mergeSortTree.cpp)
- [Minqueue - Deque](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/minqueueDeque.cpp)
- [Minqueue - Stack](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/minqueueStack.cpp)
- [Priority Queue DS](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/priority_queue_ds.cpp)
- [Order Statistic Set (GCC)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/OrderStatisticSet.cpp)
- [Range Color](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/rangeColor.cpp)
- [RMQ <O(n), O(1)>](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/rmq.cpp)
- [Sparse Table](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SparseTable.cpp)
- [Sparse Table Disjunta](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/SparseTableDisjunta.cpp)
- [Splaytree](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/splaytree.cpp)
- [Splaytree Implicita](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/splaytreeImplicita.cpp)
- [Split-Merge Set](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/splitMergeSet.cpp)
- [Split-Merge Set - Lazy](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/splitMergeSetLazy.cpp)
- [SQRT Tree](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/sqrtTree.cpp)
- [Treap](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/treap.cpp)
- [Treap Implícita](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/treapImplicita.cpp)
- [Treap Implícita Persistente](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/treapPersistent.cpp)
- [Wavelet Tree](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/WaveletTree.cpp)

### Grafos

- LCA/HLD
    - [LCA <O(n), O(1)>](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/LCA-HLD/LCA.cpp)
    - [LCA com Binary Lifting](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/LCA-HLD/LCAcomBinaryLifting.cpp)
    - [LCA com HLD](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/LCA-HLD/LCAcomHLD.cpp)
    - [Heavy-Light Decomposition - Aresta](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/LCA-HLD/HLD-aresta.cpp)
    - [Heavy-Light Decomposition - Vértice](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/LCA-HLD/HLD-vertice.cpp)
    - [Heavy-Light Decomposition sem Update](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/LCA-HLD/HLDsemUpdate.cpp)
- LCT
    - [Link-cut Tree - Aresta](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/LCT/lct-aresta.cpp)
    - [Link-cut Tree - Vertice](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/LCT/lct-vertice.cpp)
    - [Link-cut Tree Padrão](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/LCT/lct.cpp)
- [AGM Direcionada (arborescência)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/directedMST.cpp)
- [Articulation Points](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/articulationPoints.cpp)
- [Bellman-Ford](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/BellmanFord.cpp)
- [Block-Cut Tree (computa pontes e pontos de articulação)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/blockCutTree.cpp)
- [Blossom](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/blossom.cpp)
- [Centro/Diâmetro em Árvore](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/center.cpp)
- [Centroid (encontra os centroids da árvore)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/centroid.cpp)
- [Centroid Decomposition](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/centroid-decomp.cpp)
- [Centroid Tree](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/centroid-tree.cpp)
- [Dijkstra](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/dijkstra.cpp)
- [Dinitz](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/dinitz.cpp)
- [Dominator Tree](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/DominatorTree.cpp)
- [Euler Path / Euler Cycle Linear](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/eulerPath.cpp)
- [Euler Tour Tree](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/eulerTourTree.cpp)
- [Floyd-Warshall](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/FloydWarshall.cpp)
- [Functional Graph](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/functionalGraph.cpp)
- [Isomorfismo de Árvores](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/treeIsomorf.cpp)
- [Kosaraju](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/kosaraju.cpp)
- [Kruskal](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/kruskal.cpp)
- [Kuhn](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/kuhn.cpp)
- [Line Tree](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/linetree.cpp)
- [Max Flow com Lower Bound](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/lowerBoundMaxFlow.cpp)
- [MinCost-MaxFlow](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/minCostMaxFlow.cpp)
- [Prufer Code Linear](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/prufer.cpp)
- [Sack (DSU em árvores)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/sack.cpp)
- [Tarjan (SCC) e Compressão de Ciclos (bridge tree)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/tarjan.cpp)
- [Topological Sort](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/topo_sort.cpp)
- [Vertex Cover](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/cover.cpp)
- [Virtual Tree](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/virtualTree.cpp)

### Matemática

- [2-SAT (com recuperação)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/2SAT.cpp)
- [Algoritmo de Euclides Estendido](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/gcdEstendido.cpp)
- [Algoritmo Rho de Pollard (Pollard Rho)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/pollardrho.cpp)
- [Avaliação de Interpolação (avalia a interpolação em um x)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/evalInterpol.cpp)
- [Berlekamp-Massey](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/berlekampMassey.cpp)
- [Convolução de GCD / LCM](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/gcdLcmConvolution.cpp)
- [Coprime Basis](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/coprimeBasis.cpp)
- [Crivo de Eratosthenes Linear (e variações)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/crivo.cpp)
- [Detecção de Ciclo - Tortoise and Hare](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/cycleDetection.cpp)
- [Distribuição Binomial](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/probability_binomial.cpp)
- [Division Trick](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/divisionTrick.cpp)
- [Eliminação Gaussiana](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/gauss.cpp)
- [Equação Diofantina Linear](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/diofantina.cpp)
- [Eliminação Gaussiana de XOR](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/gauss_z2.cpp)
- [Exponenciação Rápida](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/fastPow.cpp)
- [Fast Walsh Hadamard Transform](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/FWHT.cpp)
- [FFT](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/convolution.cpp)
- [Integral Numérica](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/integral.cpp)
- [Inverso Modular](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/ModInverse.cpp)
- [Karatsuba](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/karatsuba.cpp)
- [Logaritmo Discreto](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/logDiscreto.cpp)
- [Miller-Rabin](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/MillerRabin.cpp)
- [Mulmod O(1)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/mulmod.cpp)
- [Simplex](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/simplex.cpp)
- [Teorema Chines do Resto](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/chinese.cpp)
- [Totiente](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Matematica/totiente.cpp)

### Primitivas

- [Aritmética Modular](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Primitivas/modularArithmetic.cpp)
- [Big Integer - C++](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Primitivas/bigint.cpp)
- [Fração](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Primitivas/frac.cpp)
- [Matroid](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Primitivas/matroid.cpp)
- [Primitivas de Matriz - Exponenciação](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Primitivas/matrix.cpp)
- [Primitivas Geométricas](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Primitivas/geometria.cpp)
- [Primitivas Geométricas Inteiras](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Primitivas/geometriaInt.cpp)
- [Primitivas Geométricas 3D](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Primitivas/geometria3D.cpp)

### Strings

- [Aho-corasick](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/ahocorasick.cpp)
- [Algoritmo Z](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/z.cpp)
- [Autômato de Sufixo](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/suffixAutomaton.cpp)
- [eertree (Palindromic Tree)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/eertree.cpp)
- [KMP](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/kmp.cpp)
- [Manacher](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/manacher.cpp)
- [Min/max suffix/cyclic shift (lexicográfico) O(n)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/min-maxSuffix-Cyclic.cpp)
- [String Hashing](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/hashing.cpp)
- [String Hashing - módulo 2^61 - 1](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/hashingLargeMod.cpp)
- [Suffix Array O(n)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/SuffixArray.cpp)
- [Suffix Array O(n log n)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/SuffixArray2.cpp)
- [Suffix Array Dinâmico](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/dynamicSuffixArray.cpp)
- [Trie](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Strings/Trie.cpp)

### Problemas

- [Algoritmo Húngaro (assignment)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/hungarian.cpp)
- [Área da Uniao de Retangulos](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/areaUniaoRetangulo.cpp)
- [Area Máxima de Histograma](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/AreaHistograma.cpp)
- [Closest Pair of Points](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/closestPairOfPoints.cpp)
- [Coeficiente Binomial Modular (para valores grandes e mod não tão grande)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/binomial.cpp)
- [Coloração de Grafo de Intervalo](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/intervalGraphColoring.cpp)
- [Conectividade Dinâmica - DSU](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/conectividadeDinamica.cpp)
- [Conectividade Dinâmica - LCT](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/conectividadeDinamica2.cpp)
- [Conjunto Independente Máximo com Peso em Grafo de Intervalo](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/intervalGraphIndSet.cpp)
- [Distância Máxima entre Dois Pontos](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/maxDist.cpp)
- [Distinct Range Query com Update](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/distinctUpdate.cpp)
- [Distinct Range Query](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/distinct2.cpp)
- [Dominator Points](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/dominatorPoints.cpp)
- [DP de Dominação 3D](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/dominacao3d.cpp)
- [Fatoração de String em Palíndromos](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/palindromicFactorization.cpp)
- [Gray Code](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/grayCode.cpp)
- [Half-Plane Intersection](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/half-plane_intersection.cpp)
- [Heap Sort](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/heapSort.cpp)
- [Interseção de Ângulos](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/angleRange.cpp)
- [Interseção de Segmentos](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/segmentIntersection.cpp)
- [Inversion Count](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/InversionCount.cpp)
- [Longest Increasing Subsequence (recuperando)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/lis.cpp)
- [Longest Increasing Subsequence (tamanho)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/lis2.cpp)
- [Minimum Enclosing Circle O(n)](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/minCirc.cpp)
- [Minkowski Sum](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/minkowski.cpp)
- [MO](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/mo.cpp)
- [MO - DSU](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/mo-dsu.cpp)
- [MO em Árvores](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/moOnTrees.cpp)
- [Parsing de Expressão](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/parsing.cpp)
- [RMQ Offline com Divide and Conquer](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/RMQoffline.cpp)
- [Sequência de de Brujin](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/deBrujin.cpp)
- [Shortest Addition Chain](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/additionChain.cpp)
- [Sweep Direction](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/sweepDirection.cpp)
- [Triangulação de Delaunay](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/delaunay.cpp)
- [Triângulos em Grafos](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/graphTriangles.cpp)
- [Verificação de Polígono Simples](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/simplePolygon.cpp)

### Extra

- [Debug](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Extra/debug.cpp)
- [fastIO](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Extra/fastIO.cpp)
- [Hash](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Extra/hash.sh)
- [Line Hash](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Extra/linehash.sh)
- [makefile](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Extra/makefile)
- [rand](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Extra/rand.cpp)
- [Stresstest](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Extra/stress.sh)
- [Template C++](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Extra/template.cpp)
- [Timer](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Extra/timer.cpp)
- [vimrc](https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Extra/vimrc)
