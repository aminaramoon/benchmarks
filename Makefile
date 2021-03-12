BOOST_LIBS="${HOME}/Applications/boost/1.74.0/include"
BOOST_INCS="${HOME}/Applications/boost/1.74.0/lib"
BENCH_LIBS="${HOME}/Applications/google_bench/3.19.0/lib" 
BENCH_INCS="${HOME}/Applications/google_bench/3.19.0/include"

bp:
	g++ -std=c++14 -O3 -DNDEBUG bp.cpp -o bp_bench -I${BOOST_INCS} -I${BENCH_INCS} -L${BENCH_LIBS} -lbenchmark -pthread

mem:
	g++ -std=c++14 -O3 -DNDEBUG cache.cpp -o mem_bench -I${BOOST_INCS} -I${BENCH_INCS} -L${BENCH_LIBS} -lbenchmark -pthread

row_col:
	g++ -std=c++14 -O3 -DNDEBUG row_column.cpp -o row_col_bench -I${BOOST_INCS} -I${BENCH_INCS} -L${BENCH_LIBS} -lbenchmark -pthread

stl:
	g++ -std=c++14 -O3 -DNDEBUG stl.cpp -o stl_bench -I${BOOST_INCS} -I${BENCH_INCS} -L${BENCH_LIBS} -lbenchmark -L${BOOST_LIBS} -pthread

restructure:
	g++ -std=c++14 -O3 -DNDEBUG restructure.cpp -o res_bench -I${BOOST_INCS} -I${BENCH_INCS} -L${BENCH_LIBS} -lbenchmark -L${BOOST_LIBS} -pthread

clean:
	@rm -rf res_bench stl_bench row_col_bench mem_bench bp_bench
