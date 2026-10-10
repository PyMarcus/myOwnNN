# Define a versão mínima do CMake exigida pelo projeto.
# É necessário para garantir que os comandos utilizados estejam disponíveis.
cmake_minimum_required(VERSION 3.20)

# Define o nome do projeto e informa que ele utiliza C++.
project(NeuralNetwork LANGUAGES CXX)

# Define o padrão C++20 para habilitar os recursos dessa versão da linguagem.
set(CMAKE_CXX_STANDARD 20)

# Exige que o compilador realmente ofereça suporte ao padrão C++20.
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Desativa extensões específicas de compiladores, priorizando o C++ padrão.
set(CMAKE_CXX_EXTENSIONS OFF)

# Adiciona a pasta include aos caminhos de busca dos arquivos de cabeçalho.
# Isso permite incluir headers do projeto sem escrever o caminho completo.
include_directories(include)

# Importa os comandos FetchContent do CMake.
# Eles permitem baixar e disponibilizar dependências durante a configuração.
include(FetchContent)

# Declara de onde o GoogleTest será obtido.
# O GoogleTest é necessário para escrever e executar testes automatizados.
FetchContent_Declare(
googletest
GIT_REPOSITORY https://github.com/google/googletest.git
GIT_TAG v1.14.0
)

# Baixa e integra o GoogleTest ao projeto, caso ainda não esteja disponível.
# Sem isso, os alvos gtest e gtest_main não estarão configurados pelo projeto.
FetchContent_MakeAvailable(googletest)

# Habilita a infraestrutura de testes do CMake/CTest.
# Isso permite registrar e executar os testes do projeto.
enable_testing()

# Busca recursivamente os arquivos .cpp dentro da pasta src.
# Eles formarão a biblioteca com a lógica central da rede neural.
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# Remove main.cpp dessa lista porque ele terá um executável próprio.
# Isso evita incluir a função main em uma biblioteca compartilhada com os testes.
list(FILTER SOURCES EXCLUDE REGEX ".*/main\\.cpp$")

# Cria uma biblioteca com a implementação central do projeto.
# Ela pode ser reutilizada tanto pelo programa principal quanto pelos testes.
add_library(neural_core ${SOURCES})

# Cria o executável principal a partir do arquivo que contém main().
add_executable(NeuralNetwork src/main.cpp)

# Vincula a lógica central ao executável principal.
# Assim, o programa consegue utilizar as classes e funções da biblioteca.
target_link_libraries(NeuralNetwork PRIVATE neural_core)

# Busca os arquivos de teste diretamente dentro da pasta tests.
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS "tests/*.cpp")

# Cria o executável responsável por rodar os testes automatizados.
add_executable(run_tests ${TEST_SOURCES})

# Vincula os testes à implementação central e às funcionalidades do GoogleTest.
# gtest fornece a infraestrutura de testes; gtest_main fornece uma main padrão.
target_link_libraries(
run_tests
PRIVATE
neural_core
GTest::gtest
GTest::gtest_main
)

# Importa os comandos que integram os testes do GoogleTest ao CTest.
include(GoogleTest)

# Descobre automaticamente os testes definidos no executável run_tests.
# Assim, cada teste descoberto pode ser listado e executado pelo CTest.
gtest_discover_tests(run_tests)
