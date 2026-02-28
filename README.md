# Fairness-Truss Community Search (FTCS)

A C++ implementation of **Fairness-aware Truss Community Search (FTCS)** — an algorithm that, given a query vertex and fairness constraints, identifies the highest-quality cohesive subgraph (measured by trussness) in which every designated attribute group is represented by at least a specified minimum count.

---

## Table of Contents

1. [Overview](#overview)
2. [Key Features](#key-features)
3. [Repository Structure](#repository-structure)
4. [Requirements](#requirements)
5. [Installation](#installation)
6. [Quickstart](#quickstart)
7. [Parameters](#parameters)
8. [Dataset Format](#dataset-format)
9. [Output Format](#output-format)
10. [Reproducibility](#reproducibility)
11. [Experiments & Datasets](#experiments--datasets)
12. [Contributing](#contributing)
13. [Acknowledgements](#acknowledgements)

---

## Overview

Community search aims to find a cohesive subgraph containing a given query vertex. FTCS extends classical truss-based community search by incorporating a **fairness constraint**: the returned community must contain at least θ (*theta*) vertices from each attribute group present in the graph. This ensures that the discovered community is not only structurally cohesive but also demographically balanced.

The algorithm proceeds in three stages:

1. **Truss Decomposition** — assigns a *trussness* value to every edge. An edge has trussness *k* if it participates in at least *k* − 2 triangles within the subgraph induced by all edges with trussness ≥ *k*.
2. **Binary Search** — finds the maximum trussness threshold *k* such that the *k*-truss community containing the query vertex still satisfies the fairness constraint.
3. **Iterative Refinement** — progressively removes vertices (guided by the γ parameter and BFS distance from the query vertex) to minimize the diameter of the community while preserving the fairness constraint and *k*-truss structure.

---

## Key Features

- **Truss-based cohesion**: communities are guaranteed to be *k*-trusses, providing strong structural guarantees.
- **Fairness enforcement**: every attribute group is represented by at least θ members in the final community.
- **Iterative diameter minimization**: the refinement loop removes distant or over-represented vertices to tighten the community around the query vertex.
- **Scalable data structures**: custom hash tables and adjacency-list structures support graphs with tens of millions of edges.
- **Detailed diagnostics**: timing breakdowns and attribute distribution statistics are written to standard error and the output file.

---

## Repository Structure

```
Fairness-Truss-Community-Search/
├── main.cpp        # Entry point: argument parsing, graph loading, FTCS driver
├── truss.hpp       # Truss decomposition algorithm
├── utils.hpp       # Core data structures (Graph, HashTable, edge_link, utilities)
├── process.cpp     # Standalone preprocessing utility: k-core decomposition
│                   # (used to identify candidate query vertices)
└── README.md       # This document
```

Dataset and output directories (created by the user):

```
./Dataset/<DatasetName>/<DatasetName>.txt   # Input graph file
./output/<DatasetName>/                     # Output files written here automatically
```

---

## Requirements

| Component | Minimum Version | Notes |
|-----------|-----------------|-------|
| C++ compiler | GCC 7 or later | Must support C++17; `g++` recommended |
| Standard library | C++17 STL | Uses `<bits/stdc++.h>` |
| RAM | ≥ 16 GB (DBLP), ≥ 64 GB (com-lj.ungraph) | Dataset-dependent; see [Experiments & Datasets](#experiments--datasets) |
| Storage | Dataset-dependent | See [Experiments & Datasets](#experiments--datasets) |

No external libraries or build systems are required.

---

## Installation

Clone the repository and compile the main executable:

```bash
git clone https://github.com/lyuzlion/Fairness-Truss-Community-Search.git
cd Fairness-Truss-Community-Search
g++ -O2 -std=c++17 -o main main.cpp
```

To compile the preprocessing utility separately:

```bash
g++ -O2 -std=c++17 -o process process.cpp
```

> **Note**: The source files contain commented-out GCC optimization pragmas (`#pragma GCC optimize`, `#pragma GCC target`). These can be uncommented for additional performance on supported hardware, though they are not required for correctness.

---

## Quickstart

1. **Prepare the dataset directory:**

   ```bash
   mkdir -p ./Dataset/DBLP
   # Place the DBLP graph file at:
   #   ./Dataset/DBLP/DBLP.txt
   ```

2. **Prepare the output directory:**

   ```bash
   mkdir -p ./output/DBLP
   ```

3. **Run FTCS:**

   ```bash
   ./main DBLP 500 40000 2 5
   ```

   This searches for a fair community containing query vertex `40000`, requiring at least `500` members per attribute group, with `2` attribute classes and γ = `5`.

4. **Inspect results:**

   Output is written to:
   ```
   ./output/DBLP/theta_500_q_40000_R_2_gamma_5.txt
   ```

---

## Parameters

```
./main <dataset_name> <theta> <q> <attribute_range> <gamma>
```

| Parameter | Type | Description |
|-----------|------|-------------|
| `dataset_name` | string | Name of the dataset. The program reads `./Dataset/<dataset_name>/<dataset_name>.txt`. |
| `theta` (θ) | integer | Minimum number of vertices from each attribute group required in the result community. |
| `q` | integer | Query vertex ID (1-indexed). The result community must contain this vertex. |
| `attribute_range` | integer | Number of distinct attribute classes in the graph (e.g., `2` for binary attributes). |
| `gamma` (γ) | integer | Number of candidate vertices removed per refinement iteration. Larger values accelerate convergence but may reduce result quality. |

**Example invocations:**

```bash
# DBLP dataset
./main DBLP 500 40000 2 5

# LiveJournal dataset
./main com-lj.ungraph 100000 101000 2 1000
```

---

## Dataset Format

Each dataset is a plain-text file structured as follows:

```
<n> <m>
<u1> <v1>
<u2> <v2>
...
<um> <vm>
<phi_1> <phi_2> ... <phi_n>
```

| Field | Description |
|-------|-------------|
| `n` | Maximum vertex ID (vertices are 1-indexed; IDs range from 1 to *n*). |
| `m` | Number of edges. |
| `u_i`, `v_i` | Endpoints of the *i*-th edge (undirected; self-loops and duplicate edges are skipped). |
| `phi_i` | Attribute class of vertex *i* (0-indexed; values in `[0, attribute_range − 1]`). |

**File placement:**

```
./Dataset/<DatasetName>/<DatasetName>.txt
```

**Example** (small graph with 4 vertices, 4 edges, 2 attribute classes):

```
4 4
1 2
1 3
2 3
3 4
0 1 0 1
```

---

## Output Format

Results are written to `./output/<dataset_name>/theta_<theta>_q_<q>_R_<attribute_range>_gamma_<gamma>.txt`.

The output file contains:

```
Overall running time: <seconds>s.
diameter : <diameter>
max_attr : <maximum attribute-group count>
min_attr : <minimum attribute-group count>
attribute delta : <max_attr - min_attr>
final attribute distribution :
<count_attr_0> <count_attr_1> ...


ans.V.size: <community size>
<vertex_id> <attribute>
...

<u> <v>
...
```

Diagnostic timing information (truss decomposition time, binary search time, per-iteration distance and maintenance time) is printed to **standard error**.

---

## Reproducibility

This section provides step-by-step instructions to reproduce experiments using FTCS.

### Environment

| Item | Recommended |
|------|-------------|
| Operating system | Linux (Ubuntu 20.04 or later recommended) |
| Compiler | GCC 11, invoked as `g++` |
| C++ standard | C++17 (`-std=c++17`) |
| RAM | ≥ 16 GB for DBLP; ≥ 64 GB for com-lj.ungraph (see [Experiments & Datasets](#experiments--datasets)) |

### Step 1 — Obtain the Source Code

```bash
git clone https://github.com/lyuzlion/Fairness-Truss-Community-Search.git
cd Fairness-Truss-Community-Search
```

### Step 2 — Compile

```bash
g++ -O2 -std=c++17 -o main main.cpp
```

### Step 3 — Prepare a Dataset

Place the dataset file in the required location:

```bash
mkdir -p ./Dataset/DBLP
# Copy or download DBLP.txt to ./Dataset/DBLP/DBLP.txt
```

The DBLP co-authorship graph is available from the [SNAP repository](https://snap.stanford.edu/data/com-DBLP.html). Vertex attributes are not included in the raw SNAP files and must be appended as a space-separated line of *n* integers (one per vertex, values in `[0, attribute_range − 1]`) at the end of the graph file, following the [Dataset Format](#dataset-format) specification. For testing purposes, synthetic binary attributes may be generated with any script (e.g., assigning `phi[i] = i % attribute_range` for each vertex *i*) and appended accordingly.

### Step 4 — Prepare the Output Directory

```bash
mkdir -p ./output/DBLP
```

### Step 5 — Run the Algorithm

```bash
./main DBLP 500 40000 2 5
```

Expected standard-error output (timings will vary by hardware):

```
Loading ./Dataset/DBLP/DBLP.txt
theta: 500, q: 40000, attribute range: 2, gamma: 5
...
Truss decomposition completed.
FTCS running...
Binary search running time: X.XXs.
Delete running time: X.XXs.
FTCS completed.
Diameter calculation completed.
```

Expected result file: `./output/DBLP/theta_500_q_40000_R_2_gamma_5.txt`

### Step 6 — Verify Output

The result file should begin with:

```
Overall running time: <seconds>s.
diameter : <integer>
max_attr : <integer>
min_attr : <integer ≥ theta>
attribute delta : <integer>
final attribute distribution :
```

**Determinism**: The FTCS algorithm is deterministic for a given input file and parameter set. Repeated runs with identical inputs will produce identical communities and metrics.

### Step 7 — Identify Query Vertices (Optional)

To identify candidate query vertices with high coreness (as used in experiments), compile and run the preprocessing utility after updating the hardcoded paths in `process.cpp`:

```bash
g++ -O2 -std=c++17 -o process process.cpp
./process
```

This performs k-core decomposition and prints vertices with coreness ≥ 20 along with their coreness values.

---

## Experiments & Datasets

The following datasets are referenced in the codebase:

| Dataset | Vertices | Edges | Notes |
|---------|----------|-------|-------|
| `facebook_combined` | 4,039 | 88,234 | Facebook social circles (SNAP) |
| `DBLP` | 500,000 | 1,049,866 | DBLP co-authorship network (SNAP) |
| `com-lj.ungraph` | 4,040,000 | 34,681,189 | LiveJournal social network (SNAP) |

All three graphs are available from the [Stanford Network Analysis Project (SNAP)](https://snap.stanford.edu/data/).

Vertex attribute files must be constructed separately and appended to the graph file as described in [Dataset Format](#dataset-format). For synthetic testing, any integer mapping `phi[i] ∈ [0, attribute_range − 1]` may be used.

---

## Contributing

Contributions are welcome. Please follow these guidelines:

1. Fork the repository and create a feature branch.
2. Ensure your code compiles without warnings under `g++ -O2 -std=c++17 -Wall`.
3. Document any new parameters or data structure changes in this README.
4. Open a pull request with a clear description of the change and its motivation.

---

## Acknowledgements

This project implements ideas related to fair community search on attributed graphs. The truss decomposition procedure follows established algorithms from the graph mining literature. The SNAP datasets used for evaluation are publicly provided by the [Stanford Network Analysis Project](https://snap.stanford.edu/).
