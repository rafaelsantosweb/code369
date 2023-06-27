<?php

foreach ([2, 3, 4, 5, 6] as $nid) {
  $node = \Drupal\node\Entity\Node::load($nid);
  $node->set('type', 'detail');
  $node->save();
  echo "Node $nid updated.\n";
}
