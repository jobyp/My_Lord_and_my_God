let length l =
  let rec length_aux l n =
    match l with
    | [] -> n
    | _ :: t -> length_aux t (n + 1)
  in
  length_aux l 0


let rec take n l =
  if n <= 0
  then []
  else
    match l with
    | []     -> []
    | h :: t -> h :: take (n - 1) t


let rec drop n l =
  if n <= 0
  then l
  else
    match l with
    | []     -> []
    | _ :: t -> drop (n - 1) t


let rec merge x y =
  match x, y with
  | [], l              -> l
  | l, []              -> l
  | hx :: tx, hy :: ty ->
     if hx <= hy
     then hx :: merge tx (hy :: ty)
     else hy :: merge (hx :: tx) ty


let rec msort l =
  match l with
  | []  -> []
  | [x] -> [x]
  | _   ->
     let n = length l / 2 in
     let left = take n l in
     let right = drop n l in
     merge (msort left) (msort right)


let () =
  print_endline "OCaml with static linking!"

