// Integracao Numerica
// 
// Metodo de Simpson 3/8
// Integra f no intervalo [a, b], erro cresce proporcional a (b - a)^5

const int N = 3*100; // multiplo de 3
ld integrate(ld a, ld b, function<ld(ld)> f) {
    ld s = 0, h = (b - a)/N;
    for (int i = 1 ; i < N; i++) s += f(a + i*h)*(i%3 ? 3 : 2);
    return (f(a) + s + f(b))*3*h/8;
}
