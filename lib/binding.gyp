{
  "targets": [
    {
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      "target_name": "game",
      "sources": [ "game.cpp" ]
    }
  ]
}