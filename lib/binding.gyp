{
  "targets": [
    {
      "target_name": "game",
      "sources": [ 
        "game.cpp", "tree.cpp"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}