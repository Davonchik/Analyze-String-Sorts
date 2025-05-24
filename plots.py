import os
import matplotlib.pyplot as plt
import math

def read_data(filepath):
    sizes = []
    comparisons = []
    times = []
    with open(filepath, 'r') as f:
        for line in f:
            parts = line.strip().split()
            if len(parts) >= 3:
                sizes.append(int(parts[0]))
                comparisons.append(float(parts[1]))
                times.append(float(parts[2]))
    return sizes, comparisons, times

def plot_test_results(test_dir, test_name):

    algorithms = [
        "ClassicMergeSort",
        "ClassicQuickSort",
        "StringMergeSort",
        #"StringTernaryQuickSort",
        "StringTernaryQuickSortPrinceton",
        "MsdStringSort",
        "MsdQuickStringSort",
    ]
    
    # Создаем папку для графиков, если ее нет
    os.makedirs(f"plots/{test_name}", exist_ok=True)
    
    plt.figure(figsize=(15, 15))
    
    # График сравнений
    plt.subplot(2, 1, 1)

    for algo in algorithms:
        filepath = f"{test_dir}/{algo}.txt"
        if os.path.exists(filepath):
            sizes, comparisons, _ = read_data(filepath)
            theoretical_edge = sizes.copy()
            plt.plot(sizes, comparisons, label=algo)

    theoretical_edge = [x * math.log(x, 74) * math.log(x, 2) for x in theoretical_edge]
    plt.plot(sizes, theoretical_edge, label="$n \\log{n} + n\\log_{\\Sigma}{n}$")

    plt.title(f"Number of comparisons - {test_name}")
    plt.xlabel("Array size")
    plt.ylabel("Comparisons")
    plt.grid(True)
    plt.legend()
    
    # График времени
    plt.subplot(2, 1, 2)
    for algo in algorithms:
        filepath = f"{test_dir}/{algo}.txt"
        if os.path.exists(filepath):
            sizes, _, times = read_data(filepath)
            plt.plot(sizes, times, label=algo)
    
    plt.title(f"Execution time - {test_name}")
    plt.xlabel("Array size")
    plt.ylabel("Time (ms)")
    plt.grid(True)
    plt.legend()
    
    plt.tight_layout()
    plt.savefig(f"plots/{test_name}/results.png")
    plt.close()

def main():
    tests = {
        "random": "results/random",
        "near_sorted": "results/near_sorted",
        "reversed": "results/reversed",
        "special": "results/special"
    }
    
    os.makedirs("plots", exist_ok=True)
    
    for test_name, test_dir in tests.items():
        print(f"Processing {test_name}...")
        plot_test_results(test_dir, test_name)

if __name__ == "__main__":
    main()