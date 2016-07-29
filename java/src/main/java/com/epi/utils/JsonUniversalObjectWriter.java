package com.epi.utils;

import com.epi.BinarySearchTreePrototypeTemplate;
import com.epi.BinaryTreePrototypeTemplate;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

import javax.json.Json;
import javax.json.JsonArrayBuilder;
import javax.json.JsonObjectBuilder;

public class JsonUniversalObjectWriter {
  public interface CustomJsonAdapter {
    public void write(JsonObjectBuilder b);
  }

  private interface Handler {
    void handle(JsonObjectBuilder builder, String name, Object o);
    void handle(JsonArrayBuilder builder, Object o);
  }

  private static final Map<Class, Handler> dispatch = new HashMap<Class, Handler>();

  static {
    dispatch.put(Integer.class, new Handler() {
      @Override
      public void handle(JsonObjectBuilder builder, String name, Object o) {
        builder.add(name, (Integer) o);
      }

      @Override
      public void handle(JsonArrayBuilder builder, Object o) {
        builder.add((Integer) o);
      }
    });
    dispatch.put(String.class, new Handler() {
      @Override
      public void handle(JsonObjectBuilder builder, String name, Object o) {
        builder.add(name, (String) o);
      }

      @Override
      public void handle(JsonArrayBuilder builder, Object o) {
        builder.add((String) o);
      }
    });
    dispatch.put(Boolean.class, new Handler() {
      @Override
      public void handle(JsonObjectBuilder builder, String name, Object o) {
        builder.add(name, (Boolean) o);
      }

      @Override
      public void handle(JsonArrayBuilder builder, Object o) {
        builder.add((Boolean) o);
      }
    });
    dispatch.put(Double.class, new Handler() {
      @Override
      public void handle(JsonObjectBuilder builder, String name, Object o) {
        builder.add(name, (Double) o);
      }

      @Override
      public void handle(JsonArrayBuilder builder, Object o) {
        builder.add((Double) o);
      }
    });
    dispatch.put(Long.class, new Handler() {
      @Override
      public void handle(JsonObjectBuilder builder, String name, Object o) {
        builder.add(name, (Long) o);
      }

      @Override
      public void handle(JsonArrayBuilder builder, Object o) {
        builder.add((Long) o);
      }
    });
    dispatch.put(Short.class, new Handler() {
      @Override
      public void handle(JsonObjectBuilder builder, String name, Object o) {
        builder.add(name, (Short) o);
      }

      @Override
      public void handle(JsonArrayBuilder builder, Object o) {
        builder.add((Short) o);
      }
    });
  }

  public static void handle(JsonObjectBuilder builder, String name, Object o) {
    if (o == null) {
      builder.addNull(name);
      return;
    }
    if (o instanceof List<?>) {
      handleList(builder, name, (List<?>) o);
      return;
    }
    if (o instanceof Set<?>) {
      handleSet(builder, name, (Set<?>) o);
      return;
    }
    if (o instanceof BinaryTreePrototypeTemplate.BinaryTreeNode<?>) {
      handle(builder, name, ((BinaryTreePrototypeTemplate.BinaryTreeNode<?>)o).toList());
      return;
    }
    if (o instanceof BinarySearchTreePrototypeTemplate.BSTNode<?>) {
      handle(builder, name, ((BinarySearchTreePrototypeTemplate.BSTNode<?>)o).toList());
      return;
    }
    if (o instanceof CustomJsonAdapter) {
      JsonObjectBuilder tmp = Json.createObjectBuilder();
      ((CustomJsonAdapter)o).write(tmp);
      builder.add(name, tmp);
      return;
    }
    Handler h = dispatch.get(o.getClass());
    if (h == null)
      builder.add(name, o.toString());
    else
      h.handle(builder, name, o);
  }

  public static void handle(JsonArrayBuilder builder, Object o) {
    if (o == null) {
      builder.addNull();
      return;
    }
    if (o instanceof List<?>) {
      handleList(builder, (List<?>) o);
      return;
    }
    if (o instanceof Set<?>) {
      handleSet(builder, (Set<?>) o);
      return;
    }
    if (o instanceof BinaryTreePrototypeTemplate.BinaryTreeNode<?>) {
      handle(builder, ((BinaryTreePrototypeTemplate.BinaryTreeNode<?>)o).toList());
      return;
    }
    if (o instanceof BinarySearchTreePrototypeTemplate.BSTNode<?>) {
      handle(builder, ((BinarySearchTreePrototypeTemplate.BSTNode<?>)o).toList());
      return;
    }
    if (o instanceof CustomJsonAdapter) {
      JsonObjectBuilder tmp = Json.createObjectBuilder();
      ((CustomJsonAdapter)o).write(tmp);
      builder.add(tmp);
      return;
    }
    Handler h = dispatch.get(o.getClass());
    if (h == null)
      builder.add(o.toString());
    else
      h.handle(builder, o);
  }

  private static <T> void handleList(JsonObjectBuilder builder, String name, List<T> l) {
    JsonArrayBuilder arrayBuilder = Json.createArrayBuilder();
    for (T elem : l)
      handle(arrayBuilder, elem);
    builder.add(name, arrayBuilder);
  }

  private static <T> void handleList(JsonArrayBuilder builder, List<T> l) {
    JsonArrayBuilder arrayBuilder = Json.createArrayBuilder();
    for (T elem : l)
      handle(arrayBuilder, elem);
    builder.add(arrayBuilder);
  }

  private static <T> void handleSet(JsonObjectBuilder builder, String name, Set<T> s) {
    JsonArrayBuilder arrayBuilder = Json.createArrayBuilder();
    for (T elem : s)
      handle(arrayBuilder, elem);
    builder.add(name, arrayBuilder);
  }

  private static <T> void handleSet(JsonArrayBuilder builder, Set<T> s) {
    JsonArrayBuilder arrayBuilder = Json.createArrayBuilder();
    for (T elem : s)
      handle(arrayBuilder, elem);
    builder.add(arrayBuilder);
  }

  public static void main(String[] args) {
    JsonObjectBuilder b = Json.createObjectBuilder();
    //Tests
    b.add("test", 0);
    System.out.println(b.build().toString());
  }
}
